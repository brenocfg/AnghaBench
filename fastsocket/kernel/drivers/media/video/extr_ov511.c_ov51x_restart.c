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
struct usb_ov511 {scalar_t__ bclass; scalar_t__ stopped; } ;

/* Variables and functions */
 scalar_t__ BCL_OV518 ; 
 int /*<<< orphan*/  PDEBUG (int,char*) ; 
 int R51x_SYS_RESET ; 
 int reg_w (struct usb_ov511*,int,int) ; 

__attribute__((used)) static inline int
ov51x_restart(struct usb_ov511 *ov)
{
	if (ov->stopped) {
		PDEBUG(4, "restarting");
		ov->stopped = 0;

		/* Reinitialize the stream */
		if (ov->bclass == BCL_OV518)
			reg_w(ov, 0x2f, 0x80);

		return (reg_w(ov, R51x_SYS_RESET, 0x00));
	}

	return 0;
}