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

/* Variables and functions */
 int /*<<< orphan*/  PLDI2CCND ; 
 int /*<<< orphan*/  PLDI2CDATA ; 
 int /*<<< orphan*/  PLDI2CSTEN ; 
 int PLDI2CSTEN_STEN ; 
 int /*<<< orphan*/  PLDI2CSTS ; 
 int PLDI2CSTS_BB ; 
 int ar_inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar_outl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  wait_acknowledge () ; 
 int /*<<< orphan*/  wait_for_vsync () ; 

void iic(int n, unsigned long addr, unsigned long data1, unsigned long data2,
	 unsigned long data3)
{
	int i;

	/* Slave Address */
	ar_outl(addr, PLDI2CDATA);
	wait_for_vsync();

	/* Start */
	ar_outl(1, PLDI2CCND);
	wait_acknowledge();

	/* Transfer data 1 */
	ar_outl(data1, PLDI2CDATA);
	wait_for_vsync();
	ar_outl(PLDI2CSTEN_STEN, PLDI2CSTEN);
	wait_acknowledge();

	/* Transfer data 2 */
	ar_outl(data2, PLDI2CDATA);
	wait_for_vsync();
	ar_outl(PLDI2CSTEN_STEN, PLDI2CSTEN);
	wait_acknowledge();

	if (n == 3) {
		/* Transfer data 3 */
		ar_outl(data3, PLDI2CDATA);
		wait_for_vsync();
		ar_outl(PLDI2CSTEN_STEN, PLDI2CSTEN);
		wait_acknowledge();
	}

	/* Stop */
	for (i = 0; i < 100; i++)
		cpu_relax();
	ar_outl(2, PLDI2CCND);
	ar_outl(2, PLDI2CCND);

	while (ar_inl(PLDI2CSTS) & PLDI2CSTS_BB)
		cpu_relax();
}