#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mkiss {int rcount; scalar_t__ buffsize; unsigned char* rbuff; int /*<<< orphan*/  buflock; int /*<<< orphan*/  flags; TYPE_2__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_over_errors; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXF_ERROR ; 
 int /*<<< orphan*/  AXF_ESCAPE ; 
 int /*<<< orphan*/  AXF_KEEPTEST ; 
#define  END 131 
#define  ESC 130 
#define  ESC_END 129 
#define  ESC_ESC 128 
 int /*<<< orphan*/  ax_bump (struct mkiss*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kiss_unesc(struct mkiss *ax, unsigned char s)
{
	switch (s) {
	case END:
		/* drop keeptest bit = VSV */
		if (test_bit(AXF_KEEPTEST, &ax->flags))
			clear_bit(AXF_KEEPTEST, &ax->flags);

		if (!test_and_clear_bit(AXF_ERROR, &ax->flags) && (ax->rcount > 2))
			ax_bump(ax);

		clear_bit(AXF_ESCAPE, &ax->flags);
		ax->rcount = 0;
		return;

	case ESC:
		set_bit(AXF_ESCAPE, &ax->flags);
		return;
	case ESC_ESC:
		if (test_and_clear_bit(AXF_ESCAPE, &ax->flags))
			s = ESC;
		break;
	case ESC_END:
		if (test_and_clear_bit(AXF_ESCAPE, &ax->flags))
			s = END;
		break;
	}

	spin_lock_bh(&ax->buflock);
	if (!test_bit(AXF_ERROR, &ax->flags)) {
		if (ax->rcount < ax->buffsize) {
			ax->rbuff[ax->rcount++] = s;
			spin_unlock_bh(&ax->buflock);
			return;
		}

		ax->dev->stats.rx_over_errors++;
		set_bit(AXF_ERROR, &ax->flags);
	}
	spin_unlock_bh(&ax->buflock);
}