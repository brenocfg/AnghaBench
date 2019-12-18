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
struct TYPE_2__ {int /*<<< orphan*/  (* l2l3 ) (struct PStack*,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  flag; } ;
struct PStack {TYPE_1__ l2; } ;

/* Variables and functions */
 int CONFIRM ; 
 int DL_RELEASE ; 
 int /*<<< orphan*/  FLG_PEND_REL ; 
 int INDICATION ; 
 int /*<<< orphan*/  stub1 (struct PStack*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
st5_dl_release_l2l3(struct PStack *st)
{
		int pr;

		if(test_and_clear_bit(FLG_PEND_REL, &st->l2.flag))
			pr = DL_RELEASE | CONFIRM;
		else
			pr = DL_RELEASE | INDICATION;

		st->l2.l2l3(st, pr, NULL);
}