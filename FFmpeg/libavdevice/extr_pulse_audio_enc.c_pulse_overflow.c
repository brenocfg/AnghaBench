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
typedef  int /*<<< orphan*/  pa_stream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DEV_TO_APP_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  avdevice_dev_to_app_control_message (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pulse_overflow(pa_stream *stream, void *userdata)
{
    AVFormatContext *h = userdata;
    avdevice_dev_to_app_control_message(h, AV_DEV_TO_APP_BUFFER_OVERFLOW, NULL, 0);
}