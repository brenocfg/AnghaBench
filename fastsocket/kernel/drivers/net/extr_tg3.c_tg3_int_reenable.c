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
struct tg3_napi {int last_tag; int coal_now; int /*<<< orphan*/  int_mbox; struct tg3* tp; } ;
struct tg3 {int coalesce_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTCC_MODE ; 
 int HOSTCC_MODE_ENABLE ; 
 int /*<<< orphan*/  TAGGED_STATUS ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 scalar_t__ tg3_has_work (struct tg3_napi*) ; 
 int /*<<< orphan*/  tw32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tw32_mailbox (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tg3_int_reenable(struct tg3_napi *tnapi)
{
	struct tg3 *tp = tnapi->tp;

	tw32_mailbox(tnapi->int_mbox, tnapi->last_tag << 24);
	mmiowb();

	/* When doing tagged status, this work check is unnecessary.
	 * The last_tag we write above tells the chip which piece of
	 * work we've completed.
	 */
	if (!tg3_flag(tp, TAGGED_STATUS) && tg3_has_work(tnapi))
		tw32(HOSTCC_MODE, tp->coalesce_mode |
		     HOSTCC_MODE_ENABLE | tnapi->coal_now);
}