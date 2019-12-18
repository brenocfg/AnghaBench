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
struct usb_gadget {int dummy; } ;
struct m66592 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M66592_FRMNUM ; 
 struct m66592* gadget_to_m66592 (struct usb_gadget*) ; 
 int m66592_read (struct m66592*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int m66592_get_frame(struct usb_gadget *_gadget)
{
	struct m66592 *m66592 = gadget_to_m66592(_gadget);
	return m66592_read(m66592, M66592_FRMNUM) & 0x03FF;
}