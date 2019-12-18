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
typedef  int /*<<< orphan*/  u8 ;
struct urb {int dummy; } ;
struct u132_ring {int /*<<< orphan*/  number; } ;
struct u132_endp {int /*<<< orphan*/  usb_endp; } ;
struct u132 {int /*<<< orphan*/  platform_dev; } ;

/* Variables and functions */
 int usb_ftdi_elan_edset_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct u132_endp*,struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (void*,struct urb*,int /*<<< orphan*/ *,int,int,int,int,int,int,int,int,int)) ; 

__attribute__((used)) static inline int edset_output(struct u132 *u132, struct u132_ring *ring,
	struct u132_endp *endp, struct urb *urb, u8 address, u8 toggle_bits,
	void (*callback) (void *endp, struct urb *urb, u8 *buf, int len,
	int toggle_bits, int error_count, int condition_code, int repeat_number,
	 int halted, int skipped, int actual, int non_null))
{
	return usb_ftdi_elan_edset_output(u132->platform_dev, ring->number,
		endp, urb, address, endp->usb_endp, toggle_bits, callback);
}