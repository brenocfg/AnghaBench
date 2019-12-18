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
struct TYPE_2__ {scalar_t__ tx_size; int /*<<< orphan*/  tx_buffer; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ wiiu_adapter_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int int32_t ;

/* Variables and functions */
 int HIDSetReport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int32_t wiiu_hid_set_report(void *data, uint8_t report_type,
               uint8_t report_id, void *report_data, uint32_t report_length)
{
   wiiu_adapter_t *adapter = (wiiu_adapter_t *)data;
   if (!adapter || report_length > adapter->tx_size)
      return -1;

   memset(adapter->tx_buffer, 0, adapter->tx_size);
   memcpy(adapter->tx_buffer, report_data, report_length);

   return HIDSetReport(adapter->handle,
         report_type,
         report_id,
         adapter->tx_buffer,
         adapter->tx_size,
         NULL, NULL);
}