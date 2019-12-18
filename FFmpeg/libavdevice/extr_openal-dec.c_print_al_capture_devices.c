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

/* Variables and functions */
 int /*<<< orphan*/  ALC_CAPTURE_DEVICE_SPECIFIER ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 char* alcGetString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static inline void print_al_capture_devices(void *log_ctx)
{
    const char *devices;

    if (!(devices = alcGetString(NULL, ALC_CAPTURE_DEVICE_SPECIFIER)))
        return;

    av_log(log_ctx, AV_LOG_INFO, "List of OpenAL capture devices on this system:\n");

    for (; *devices != '\0'; devices += strlen(devices) + 1)
        av_log(log_ctx, AV_LOG_INFO, "  %s\n", devices);
}