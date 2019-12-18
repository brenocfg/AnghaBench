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
 int /*<<< orphan*/  ANDROID_LOG_INFO ; 
 int /*<<< orphan*/  __android_log_print (int /*<<< orphan*/ ,char*,char*,char*) ; 

void log_callback(char * message)
{
    __android_log_print(ANDROID_LOG_INFO, "yabause", "%s", message);
}