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
struct TYPE_2__ {unsigned int dataacc; scalar_t__ skip; scalar_t__ count; int /*<<< orphan*/  addr; scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSYNC () ; 
 int HW_WATCHPOINT_NUM ; 
 unsigned int WPDACC0_OFFSET ; 
 unsigned int WPDACC1_OFFSET ; 
 unsigned int WPDAEN0 ; 
 unsigned int WPDAEN1 ; 
 unsigned int WPDCNTEN0 ; 
 unsigned int WPDCNTEN1 ; 
 unsigned int WPDSRC0 ; 
 unsigned int WPDSRC1 ; 
 unsigned int WPIAEN0 ; 
 unsigned int WPIAEN1 ; 
 unsigned int WPIAEN2 ; 
 unsigned int WPIAEN3 ; 
 unsigned int WPIAEN4 ; 
 unsigned int WPIAEN5 ; 
 unsigned int WPICNTEN0 ; 
 unsigned int WPICNTEN1 ; 
 unsigned int WPICNTEN2 ; 
 unsigned int WPICNTEN3 ; 
 unsigned int WPICNTEN4 ; 
 unsigned int WPICNTEN5 ; 
 unsigned int WPPWR ; 
 int /*<<< orphan*/  bfin_write_WPDA0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_WPDA1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_WPDACNT0 (scalar_t__) ; 
 int /*<<< orphan*/  bfin_write_WPDACNT1 (scalar_t__) ; 
 int /*<<< orphan*/  bfin_write_WPDACTL (unsigned int) ; 
 int /*<<< orphan*/  bfin_write_WPIA0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_WPIA1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_WPIA2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_WPIA3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_WPIA4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_WPIA5 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_WPIACNT0 (scalar_t__) ; 
 int /*<<< orphan*/  bfin_write_WPIACNT1 (scalar_t__) ; 
 int /*<<< orphan*/  bfin_write_WPIACNT2 (scalar_t__) ; 
 int /*<<< orphan*/  bfin_write_WPIACNT3 (scalar_t__) ; 
 int /*<<< orphan*/  bfin_write_WPIACNT4 (scalar_t__) ; 
 int /*<<< orphan*/  bfin_write_WPIACNT5 (scalar_t__) ; 
 int /*<<< orphan*/  bfin_write_WPIACTL (unsigned int) ; 
 TYPE_1__* breakinfo ; 

void bfin_correct_hw_break(void)
{
	int breakno;
	unsigned int wpiactl = 0;
	unsigned int wpdactl = 0;
	int enable_wp = 0;

	for (breakno = 0; breakno < HW_WATCHPOINT_NUM; breakno++)
		if (breakinfo[breakno].enabled) {
			enable_wp = 1;

			switch (breakno) {
			case 0:
				wpiactl |= WPIAEN0|WPICNTEN0;
				bfin_write_WPIA0(breakinfo[breakno].addr);
				bfin_write_WPIACNT0(breakinfo[breakno].count
					+ breakinfo->skip);
				break;
			case 1:
				wpiactl |= WPIAEN1|WPICNTEN1;
				bfin_write_WPIA1(breakinfo[breakno].addr);
				bfin_write_WPIACNT1(breakinfo[breakno].count
					+ breakinfo->skip);
				break;
			case 2:
				wpiactl |= WPIAEN2|WPICNTEN2;
				bfin_write_WPIA2(breakinfo[breakno].addr);
				bfin_write_WPIACNT2(breakinfo[breakno].count
					+ breakinfo->skip);
				break;
			case 3:
				wpiactl |= WPIAEN3|WPICNTEN3;
				bfin_write_WPIA3(breakinfo[breakno].addr);
				bfin_write_WPIACNT3(breakinfo[breakno].count
					+ breakinfo->skip);
				break;
			case 4:
				wpiactl |= WPIAEN4|WPICNTEN4;
				bfin_write_WPIA4(breakinfo[breakno].addr);
				bfin_write_WPIACNT4(breakinfo[breakno].count
					+ breakinfo->skip);
				break;
			case 5:
				wpiactl |= WPIAEN5|WPICNTEN5;
				bfin_write_WPIA5(breakinfo[breakno].addr);
				bfin_write_WPIACNT5(breakinfo[breakno].count
					+ breakinfo->skip);
				break;
			case 6:
				wpdactl |= WPDAEN0|WPDCNTEN0|WPDSRC0;
				wpdactl |= breakinfo[breakno].dataacc
					<< WPDACC0_OFFSET;
				bfin_write_WPDA0(breakinfo[breakno].addr);
				bfin_write_WPDACNT0(breakinfo[breakno].count
					+ breakinfo->skip);
				break;
			case 7:
				wpdactl |= WPDAEN1|WPDCNTEN1|WPDSRC1;
				wpdactl |= breakinfo[breakno].dataacc
					<< WPDACC1_OFFSET;
				bfin_write_WPDA1(breakinfo[breakno].addr);
				bfin_write_WPDACNT1(breakinfo[breakno].count
					+ breakinfo->skip);
				break;
			}
		}

	/* Should enable WPPWR bit first before set any other
	 * WPIACTL and WPDACTL bits */
	if (enable_wp) {
		bfin_write_WPIACTL(WPPWR);
		CSYNC();
		bfin_write_WPIACTL(wpiactl|WPPWR);
		bfin_write_WPDACTL(wpdactl);
		CSYNC();
	}
}