#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {scalar_t__ (* detect ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ hid_device_t ;

/* Variables and functions */
 TYPE_1__** hid_device_list ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

hid_device_t *hid_device_driver_lookup(uint16_t vendor_id, uint16_t product_id) {
  int i = 0;

  for(i = 0; hid_device_list[i] != NULL; i++) {
    if(hid_device_list[i]->detect(vendor_id, product_id))
      return hid_device_list[i];
  }

  return NULL;
}