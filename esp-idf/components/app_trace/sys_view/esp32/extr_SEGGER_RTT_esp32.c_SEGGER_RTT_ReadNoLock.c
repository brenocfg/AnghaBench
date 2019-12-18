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
typedef  int uint32_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_APPTRACE_DEST_TRAX ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ esp_apptrace_read (int /*<<< orphan*/ ,void*,int*,int /*<<< orphan*/ ) ; 

unsigned SEGGER_RTT_ReadNoLock(unsigned BufferIndex, void* pData, unsigned BufferSize) {
  uint32_t size = BufferSize;
  esp_err_t res = esp_apptrace_read(ESP_APPTRACE_DEST_TRAX, pData, &size, 0);
  if (res != ESP_OK) {
    return 0;
  }
  return size;
}