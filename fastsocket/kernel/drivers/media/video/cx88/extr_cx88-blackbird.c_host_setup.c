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
struct cx88_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MO_GPHST_HDSHK ; 
 int /*<<< orphan*/  MO_GPHST_MODE ; 
 int /*<<< orphan*/  MO_GPHST_MUX16 ; 
 int /*<<< orphan*/  MO_GPHST_SOFT_RST ; 
 int /*<<< orphan*/  MO_GPHST_WDTH ; 
 int /*<<< orphan*/  MO_GPHST_WSC ; 
 int /*<<< orphan*/  MO_GPHST_XFR ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void host_setup(struct cx88_core *core)
{
	/* toggle reset of the host */
	cx_write(MO_GPHST_SOFT_RST, 1);
	udelay(100);
	cx_write(MO_GPHST_SOFT_RST, 0);
	udelay(100);

	/* host port setup */
	cx_write(MO_GPHST_WSC, 0x44444444U);
	cx_write(MO_GPHST_XFR, 0);
	cx_write(MO_GPHST_WDTH, 15);
	cx_write(MO_GPHST_HDSHK, 0);
	cx_write(MO_GPHST_MUX16, 0x44448888U);
	cx_write(MO_GPHST_MODE, 0);
}