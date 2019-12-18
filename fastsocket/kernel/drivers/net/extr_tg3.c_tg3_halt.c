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
struct tg3_hw_stats {int dummy; } ;
struct tg3 {scalar_t__ hw_stats; int /*<<< orphan*/  estats_prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __tg3_set_mac_addr (struct tg3*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tg3_abort_hw (struct tg3*,int) ; 
 int tg3_chip_reset (struct tg3*) ; 
 int /*<<< orphan*/  tg3_get_estats (struct tg3*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tg3_get_nstats (struct tg3*) ; 
 int /*<<< orphan*/  tg3_stop_fw (struct tg3*) ; 
 int /*<<< orphan*/  tg3_write_sig_legacy (struct tg3*,int) ; 
 int /*<<< orphan*/  tg3_write_sig_post_reset (struct tg3*,int) ; 
 int /*<<< orphan*/  tg3_write_sig_pre_reset (struct tg3*,int) ; 

__attribute__((used)) static int tg3_halt(struct tg3 *tp, int kind, bool silent)
{
	int err;

	tg3_stop_fw(tp);

	tg3_write_sig_pre_reset(tp, kind);

	tg3_abort_hw(tp, silent);
	err = tg3_chip_reset(tp);

	__tg3_set_mac_addr(tp, false);

	tg3_write_sig_legacy(tp, kind);
	tg3_write_sig_post_reset(tp, kind);

	if (tp->hw_stats) {
		/* Save the stats across chip resets... */
		tg3_get_nstats(tp);
		tg3_get_estats(tp, &tp->estats_prev);

		/* And make sure the next sample is new data */
		memset(tp->hw_stats, 0, sizeof(struct tg3_hw_stats));
	}

	if (err)
		return err;

	return 0;
}