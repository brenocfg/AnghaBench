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
struct usb_ov511 {int stopped; scalar_t__ bclass; } ;

/* Variables and functions */
 scalar_t__ BCL_OV518 ; 
 int /*<<< orphan*/  PDEBUG (int,char*) ; 
 int /*<<< orphan*/  R51x_SYS_RESET ; 
 int reg_w (struct usb_ov511*,int /*<<< orphan*/ ,int) ; 
 int reg_w_mask (struct usb_ov511*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline int
ov51x_stop(struct usb_ov511 *ov)
{
	PDEBUG(4, "stopping");
	ov->stopped = 1;
	if (ov->bclass == BCL_OV518)
		return (reg_w_mask(ov, R51x_SYS_RESET, 0x3a, 0x3a));
	else
		return (reg_w(ov, R51x_SYS_RESET, 0x3d));
}