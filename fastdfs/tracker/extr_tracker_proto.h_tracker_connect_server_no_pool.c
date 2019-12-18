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
typedef  int /*<<< orphan*/  TrackerServerInfo ;
typedef  int /*<<< orphan*/  ConnectionInfo ;

/* Variables and functions */
 int /*<<< orphan*/ * tracker_connect_server_no_pool_ex (int /*<<< orphan*/ *,char const*,int*,int) ; 

__attribute__((used)) static inline ConnectionInfo *tracker_connect_server_no_pool(
        TrackerServerInfo *pServerInfo, int *err_no)
{
    const char *bind_addr = NULL;
    return tracker_connect_server_no_pool_ex(pServerInfo,
            bind_addr, err_no, true);
}