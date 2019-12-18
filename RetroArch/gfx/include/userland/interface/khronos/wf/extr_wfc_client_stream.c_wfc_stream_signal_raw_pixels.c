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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  WFCNativeStreamType ;

/* Variables and functions */
 int /*<<< orphan*/  wfc_server_stream_signal_raw_pixels (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void wfc_stream_signal_raw_pixels(WFCNativeStreamType stream, uint32_t handle,
      uint32_t format, uint32_t w, uint32_t h, uint32_t pitch, uint32_t vpitch)
{
   wfc_server_stream_signal_raw_pixels(stream, handle, format, w, h, pitch, vpitch);
}