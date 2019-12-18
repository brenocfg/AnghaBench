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
typedef  int /*<<< orphan*/  u32 ;
struct wusbhc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WUSB_KEY_INDEX_ORIGINATOR_HOST ; 
 int /*<<< orphan*/  WUSB_KEY_INDEX_TYPE_GTK ; 
 int __hwahc_dev_set_key (struct wusbhc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wusb_key_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __hwahc_op_set_gtk(struct wusbhc *wusbhc, u32 tkid,
			      const void *key, size_t key_size)
{
	u8 key_idx = wusb_key_index(0, WUSB_KEY_INDEX_TYPE_GTK,
				    WUSB_KEY_INDEX_ORIGINATOR_HOST);

	return __hwahc_dev_set_key(wusbhc, 0, tkid, key, key_size, key_idx);
}