#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct sfb {int sfb_current; } ;
struct TYPE_2__ {scalar_t__ pmark; } ;

/* Variables and functions */
 int SFB_BINMASK (int /*<<< orphan*/ ) ; 
 TYPE_1__* SFB_BINST (struct sfb*,int,int,int) ; 
 int SFB_LEVELS ; 
 scalar_t__ SFB_PMARK_TH ; 
 int /*<<< orphan*/  VERIFY (int) ; 

__attribute__((used)) static inline int
sfb_pcheck(struct sfb *sp, uint32_t pkt_sfb_hash)
{
#if SFB_LEVELS != 2
	int i, n;
#endif /* SFB_LEVELS != 2 */
	uint8_t *pkt_sfb_hash8 = (uint8_t *)&pkt_sfb_hash;
	int s;

	s = sp->sfb_current;
	VERIFY((s + (s ^ 1)) == 1);

	/*
	 * For current bins, returns 1 if all pmark >= SFB_PMARK_TH,
	 * 0 otherwise; optimize for SFB_LEVELS=2.
	 */
#if SFB_LEVELS == 2
	/*
	 * Level 0: bin index at [0] for set 0; [2] for set 1
	 * Level 1: bin index at [1] for set 0; [3] for set 1
	 */
	if (SFB_BINST(sp, 0, SFB_BINMASK(pkt_sfb_hash8[(s << 1)]),
	    s)->pmark < SFB_PMARK_TH ||
	    SFB_BINST(sp, 1, SFB_BINMASK(pkt_sfb_hash8[(s << 1) + 1]),
	    s)->pmark < SFB_PMARK_TH)
		return (0);
#else /* SFB_LEVELS != 2 */
	for (i = 0; i < SFB_LEVELS; i++) {
		if (s == 0)		/* set 0, bin index [0,1] */
			n = SFB_BINMASK(pkt_sfb_hash8[i]);
		else			/* set 1, bin index [2,3] */
			n = SFB_BINMASK(pkt_sfb_hash8[i + 2]);

		if (SFB_BINST(sp, i, n, s)->pmark < SFB_PMARK_TH)
			return (0);
	}
#endif /* SFB_LEVELS != 2 */
	return (1);
}