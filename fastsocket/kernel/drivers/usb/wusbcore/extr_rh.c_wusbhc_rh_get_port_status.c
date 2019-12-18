#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct wusbhc {scalar_t__ ports_max; int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  change; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* wusb_port_by_idx (struct wusbhc*,scalar_t__) ; 

__attribute__((used)) static int wusbhc_rh_get_port_status(struct wusbhc *wusbhc, u16 port_idx,
				     u32 *_buf, u16 wLength)
{
	__le16 *buf = (__le16 *)_buf;

	if (port_idx > wusbhc->ports_max)
		return -EINVAL;

	mutex_lock(&wusbhc->mutex);
	buf[0] = cpu_to_le16(wusb_port_by_idx(wusbhc, port_idx)->status);
	buf[1] = cpu_to_le16(wusb_port_by_idx(wusbhc, port_idx)->change);
	mutex_unlock(&wusbhc->mutex);

	return 0;
}