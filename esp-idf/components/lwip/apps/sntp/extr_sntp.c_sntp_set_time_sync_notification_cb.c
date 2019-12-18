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
typedef  int /*<<< orphan*/  sntp_sync_time_cb_t ;

/* Variables and functions */
 int /*<<< orphan*/  time_sync_notification_cb ; 

void sntp_set_time_sync_notification_cb(sntp_sync_time_cb_t callback)
{
    time_sync_notification_cb = callback;
}