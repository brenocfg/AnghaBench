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
struct uwb_rc {struct hwarc* priv; } ;
struct hwarc {scalar_t__ rd_buffer; int /*<<< orphan*/  neep_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hwarc_neep_release(struct uwb_rc *rc)
{
	struct hwarc *hwarc = rc->priv;

	usb_kill_urb(hwarc->neep_urb);
	usb_free_urb(hwarc->neep_urb);
	free_page((unsigned long)hwarc->rd_buffer);
}