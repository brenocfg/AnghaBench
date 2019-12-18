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
struct slip {int rcount; scalar_t__ buffsize; unsigned char* rbuff; int /*<<< orphan*/  flags; int /*<<< orphan*/  rx_over_errors; } ;

/* Variables and functions */
#define  END 131 
#define  ESC 130 
#define  ESC_END 129 
#define  ESC_ESC 128 
 int /*<<< orphan*/  SLF_ERROR ; 
 int /*<<< orphan*/  SLF_ESCAPE ; 
 int /*<<< orphan*/  SLF_KEEPTEST ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sl_bump (struct slip*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void slip_unesc(struct slip *sl, unsigned char s)
{

	switch (s) {
	case END:
#ifdef CONFIG_SLIP_SMART
		/* drop keeptest bit = VSV */
		if (test_bit(SLF_KEEPTEST, &sl->flags))
			clear_bit(SLF_KEEPTEST, &sl->flags);
#endif

		if (!test_and_clear_bit(SLF_ERROR, &sl->flags)
							&& (sl->rcount > 2))
			sl_bump(sl);
		clear_bit(SLF_ESCAPE, &sl->flags);
		sl->rcount = 0;
		return;

	case ESC:
		set_bit(SLF_ESCAPE, &sl->flags);
		return;
	case ESC_ESC:
		if (test_and_clear_bit(SLF_ESCAPE, &sl->flags))
			s = ESC;
		break;
	case ESC_END:
		if (test_and_clear_bit(SLF_ESCAPE, &sl->flags))
			s = END;
		break;
	}
	if (!test_bit(SLF_ERROR, &sl->flags))  {
		if (sl->rcount < sl->buffsize)  {
			sl->rbuff[sl->rcount++] = s;
			return;
		}
		sl->rx_over_errors++;
		set_bit(SLF_ERROR, &sl->flags);
	}
}