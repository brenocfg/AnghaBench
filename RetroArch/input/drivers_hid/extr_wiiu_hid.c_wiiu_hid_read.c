#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t rx_size; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ wiiu_adapter_t ;
typedef  int int32_t ;

/* Variables and functions */
 int HIDRead (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  report_hid_error (char*,TYPE_1__*,int) ; 

__attribute__((used)) static int32_t wiiu_hid_read(void *data, void *buffer, size_t size)
{
   wiiu_adapter_t *adapter = (wiiu_adapter_t *)data;
   int32_t result;

   if (!adapter)
      return -1;

   if (size > adapter->rx_size)
      return -1;

   result = HIDRead(adapter->handle, buffer, size, NULL, NULL);
   if (result < 0)
      report_hid_error("read failed", adapter, result);

   return result;
}