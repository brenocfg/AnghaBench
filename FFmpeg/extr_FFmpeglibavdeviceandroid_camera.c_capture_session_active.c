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
typedef  int /*<<< orphan*/  ACameraCaptureSession ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void capture_session_active(void *context, ACameraCaptureSession *session)
{
    av_log(context, AV_LOG_INFO, "Android camera capture session is active.\n");
}