#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u_int16_t ;
struct timespec {int dummy; } ;
struct sfbbinstats {scalar_t__ pkts; scalar_t__ pmark; } ;
struct sfb {int sfb_current; scalar_t__ sfb_allocation; int sfb_flags; } ;

/* Variables and functions */
 int SFBF_SUSPENDED ; 
 int /*<<< orphan*/  SFB_BINFT (struct sfb*,int,int,int) ; 
 int SFB_BINMASK (int /*<<< orphan*/ ) ; 
 struct sfbbinstats* SFB_BINST (struct sfb*,int,int,int) ; 
 int SFB_FC_LEVEL ; 
 int SFB_LEVELS ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int sfb_bin_mark_or_drop (struct sfb*,struct sfbbinstats*) ; 
 int /*<<< orphan*/  sfb_increment_bin (struct sfb*,struct sfbbinstats*,int /*<<< orphan*/ ,struct timespec*) ; 

__attribute__((used)) static int
sfb_drop_early(struct sfb *sp, uint32_t pkt_sfb_hash, u_int16_t *pmin,
    struct timespec *now)
{
#if SFB_LEVELS != 2
	int i;
#endif /* SFB_LEVELS != 2 */
	struct sfbbinstats *bin;
	int s, n, ret = 0;
	uint8_t *pkt_sfb_hash8 = (uint8_t *)&pkt_sfb_hash;

	s = sp->sfb_current;
	VERIFY((s + (s ^ 1)) == 1);

	*pmin = (u_int16_t)-1;

	/*
	 * Update current bins; optimize for SFB_LEVELS=2
	 */
#if SFB_LEVELS == 2
	/* Level 0: bin index at [0] for set 0; [2] for set 1 */
	n = SFB_BINMASK(pkt_sfb_hash8[(s << 1)]);
	bin = SFB_BINST(sp, 0, n, s);
	if (*pmin > (u_int16_t)bin->pmark)
		*pmin = (u_int16_t)bin->pmark;


	/* Update SFB probability */
	if (bin->pkts >= sp->sfb_allocation)
		sfb_increment_bin(sp, bin, SFB_BINFT(sp, 0, n, s), now);

	ret = sfb_bin_mark_or_drop(sp, bin);

	/* Level 1: bin index at [1] for set 0; [3] for set 1 */
	n = SFB_BINMASK(pkt_sfb_hash8[(s << 1) + 1]);
	bin = SFB_BINST(sp, 1, n, s);
	if (*pmin > (u_int16_t)bin->pmark)
		*pmin = (u_int16_t)bin->pmark;

	if (bin->pkts >= sp->sfb_allocation)
		sfb_increment_bin(sp, bin, SFB_BINFT(sp, 1, n, s), now);
#else /* SFB_LEVELS != 2 */
	for (i = 0; i < SFB_LEVELS; i++) {
		if (s == 0)		/* set 0, bin index [0,1] */
			n = SFB_BINMASK(pkt_sfb_hash8[i]);
		else			/* set 1, bin index [2,3] */
			n = SFB_BINMASK(pkt_sfb_hash8[i + 2]);

		bin = SFB_BINST(sp, i, n, s);
		if (*pmin > (u_int16_t)bin->pmark)
			*pmin = (u_int16_t)bin->pmark;

		if (bin->pkts >= sp->sfb_allocation)
			sfb_increment_bin(sp, bin,
			    SFB_BINFT(sp, i, n, s), now);
		if (i == SFB_FC_LEVEL)
			ret = sfb_bin_mark_or_drop(sp, bin);
	}
#endif /* SFB_LEVELS != 2 */

	if (sp->sfb_flags & SFBF_SUSPENDED)
		ret = 1;	/* drop or mark */

	return (ret);
}