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
typedef  int uint8_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_APPTRACE_DEST_TRAX ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,unsigned int) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  SEGGER_HOST_WAIT_TMO ; 
 int /*<<< orphan*/  SEGGER_RTT_ESP32_FlushNoLock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEGGER_STOP_WAIT_TMO ; 
 unsigned int SYSVIEW_EVENTS_BUF_SZ ; 
 int SYSVIEW_EVTID_TRACE_STOP ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ esp_apptrace_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,unsigned int) ; 
 int /*<<< orphan*/ * s_events_buf ; 
 unsigned int s_events_buf_filled ; 
 scalar_t__ xPortGetCoreID () ; 

unsigned SEGGER_RTT_WriteSkipNoLock(unsigned BufferIndex, const void* pBuffer, unsigned NumBytes) {
  uint8_t *pbuf = (uint8_t *)pBuffer;
  uint8_t event_id = *pbuf;

  if (NumBytes > SYSVIEW_EVENTS_BUF_SZ) {
      ESP_LOGE(TAG, "Too large event %u bytes!", NumBytes);
      return 0;
  }
  if (xPortGetCoreID()) { // dual core specific code
    // use the highest - 1 bit of event ID to indicate core ID
    // the highest bit can not be used due to event ID encoding method
    // this reduces supported ID range to [0..63] (for 1 byte IDs) plus [128..16383] (for 2 bytes IDs)
    if (*pbuf & 0x80) { // 2 bytes ID
      *(pbuf + 1) |= (1 << 6);
    } else if (NumBytes != 10 || *pbuf != 0) { // ignore sync sequence
      *pbuf |= (1 << 6);
    }
  }
  if (s_events_buf_filled + NumBytes > SYSVIEW_EVENTS_BUF_SZ) {
    esp_err_t res = esp_apptrace_write(ESP_APPTRACE_DEST_TRAX, s_events_buf, s_events_buf_filled, SEGGER_HOST_WAIT_TMO);
    if (res != ESP_OK) {
      return 0; // skip current data buffer only, accumulated events are kept
    }
    s_events_buf_filled = 0;
  }
  memcpy(&s_events_buf[s_events_buf_filled], pBuffer, NumBytes);
  s_events_buf_filled += NumBytes;
  if (event_id == SYSVIEW_EVTID_TRACE_STOP) {
    SEGGER_RTT_ESP32_FlushNoLock(0, SEGGER_STOP_WAIT_TMO);
  }
  return NumBytes;
}