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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 scalar_t__ PID_NONE ; 
 scalar_t__ VID_NONE ; 

__attribute__((used)) static bool hid_null_detect(uint16_t vendor_id, uint16_t product_id)
{
  return vendor_id == VID_NONE && product_id == PID_NONE;
}