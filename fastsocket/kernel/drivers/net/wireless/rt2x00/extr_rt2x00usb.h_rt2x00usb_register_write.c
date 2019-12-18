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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int dummy; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  REGISTER_TIMEOUT ; 
 int /*<<< orphan*/  USB_MULTI_WRITE ; 
 int /*<<< orphan*/  USB_VENDOR_REQUEST_OUT ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00usb_vendor_request_buff (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int const,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rt2x00usb_register_write(struct rt2x00_dev *rt2x00dev,
					    const unsigned int offset,
					    u32 value)
{
	__le32 reg = cpu_to_le32(value);
	rt2x00usb_vendor_request_buff(rt2x00dev, USB_MULTI_WRITE,
				      USB_VENDOR_REQUEST_OUT, offset,
				      &reg, sizeof(reg), REGISTER_TIMEOUT);
}