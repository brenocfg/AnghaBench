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
struct wacom_wac {char* data; } ;
struct wacom_combo {struct urb* urb; } ;
struct urb {scalar_t__ actual_length; } ;

/* Variables and functions */
 scalar_t__ WACOM_PKGLEN_TPC1FG ; 
 int /*<<< orphan*/  dbg (char*,char) ; 
 int wacom_tpc_mt_touch (struct wacom_wac*,void*) ; 
 int wacom_tpc_pen (struct wacom_wac*,void*) ; 
 int wacom_tpc_single_touch (struct wacom_wac*,void*,scalar_t__) ; 

__attribute__((used)) static int wacom_tpc_irq(struct wacom_wac *wacom, void *wcombo)
{
	char *data = wacom->data;
	struct urb *urb = ((struct wacom_combo *)wcombo)->urb;

	dbg("wacom_tpc_irq: received report #%d", data[0]);

	if (urb->actual_length == WACOM_PKGLEN_TPC1FG || data[0] == 6) /* Touch data */
		return wacom_tpc_single_touch(wacom, wcombo, urb->actual_length);
	else if (data[0] == 13)
		return wacom_tpc_mt_touch(wacom, wcombo);
	else if (data[0] == 2)
		return wacom_tpc_pen(wacom, wcombo);

	return 0;
}