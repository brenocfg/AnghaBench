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
struct usb_ov511 {scalar_t__ bclass; } ;

/* Variables and functions */
 scalar_t__ BCL_OV511 ; 
 scalar_t__ BCL_OV518 ; 
 int ENOSYS ; 
 int /*<<< orphan*/  err (char*) ; 

__attribute__((used)) static int
request_decompressor(struct usb_ov511 *ov)
{
	if (ov->bclass == BCL_OV511 || ov->bclass == BCL_OV518) {
		err("No decompressor available");
	} else {
		err("Unknown bridge");
	}

	return -ENOSYS;
}