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
typedef  int /*<<< orphan*/  sntp_sync_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  sntp_sync_status ; 

inline void sntp_set_sync_status(sntp_sync_status_t sync_status)
{
    sntp_sync_status = sync_status;
}