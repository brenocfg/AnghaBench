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
typedef  int /*<<< orphan*/  WFC_STREAM_IMAGE_T ;
typedef  int /*<<< orphan*/  WFCNativeStreamType ;

/* Variables and functions */
 int /*<<< orphan*/  wfc_server_stream_signal_image (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

void wfc_stream_signal_image(WFCNativeStreamType stream,
      const WFC_STREAM_IMAGE_T *image)
{
   wfc_server_stream_signal_image(stream, image);
}