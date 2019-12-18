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
typedef  int /*<<< orphan*/  u16 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_VENDOR_REQUEST_OUT ; 
 int rt2x00usb_vendor_request (struct rt2x00_dev*,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static inline int rt2x00usb_vendor_request_sw(struct rt2x00_dev *rt2x00dev,
					      const u8 request,
					      const u16 offset,
					      const u16 value,
					      const int timeout)
{
	return rt2x00usb_vendor_request(rt2x00dev, request,
					USB_VENDOR_REQUEST_OUT, offset,
					value, NULL, 0, timeout);
}