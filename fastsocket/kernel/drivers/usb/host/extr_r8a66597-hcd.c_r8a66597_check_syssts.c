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
typedef  scalar_t__ u16 ;
struct r8a66597 {scalar_t__ bus_suspended; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTCH ; 
 int /*<<< orphan*/  ATTCHE ; 
 int /*<<< orphan*/  DTCH ; 
 int /*<<< orphan*/  DTCHE ; 
 scalar_t__ FS_JSTS ; 
 int /*<<< orphan*/  HSE ; 
 scalar_t__ LS_JSTS ; 
 scalar_t__ SE0 ; 
 int /*<<< orphan*/  get_intenb_reg (int) ; 
 int /*<<< orphan*/  get_intsts_reg (int) ; 
 int /*<<< orphan*/  get_syscfg_reg (int) ; 
 int /*<<< orphan*/  r8a66597_bclr (struct r8a66597*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_bset (struct r8a66597*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_to_hcd (struct r8a66597*) ; 
 int /*<<< orphan*/  r8a66597_write (struct r8a66597*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_hcd_poll_rh_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_hcd_resume_root_hub (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r8a66597_check_syssts(struct r8a66597 *r8a66597, int port,
					u16 syssts)
{
	if (syssts == SE0) {
		r8a66597_write(r8a66597, ~ATTCH, get_intsts_reg(port));
		r8a66597_bset(r8a66597, ATTCHE, get_intenb_reg(port));
	} else {
		if (syssts == FS_JSTS)
			r8a66597_bset(r8a66597, HSE, get_syscfg_reg(port));
		else if (syssts == LS_JSTS)
			r8a66597_bclr(r8a66597, HSE, get_syscfg_reg(port));

		r8a66597_write(r8a66597, ~DTCH, get_intsts_reg(port));
		r8a66597_bset(r8a66597, DTCHE, get_intenb_reg(port));

		if (r8a66597->bus_suspended)
			usb_hcd_resume_root_hub(r8a66597_to_hcd(r8a66597));
	}

	usb_hcd_poll_rh_status(r8a66597_to_hcd(r8a66597));
}