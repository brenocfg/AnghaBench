#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* connections; } ;
typedef  TYPE_2__ TrackerServerInfo ;
struct TYPE_5__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int fdfs_server_info_to_string_ex (TYPE_2__ const*,int /*<<< orphan*/ ,char*,int const) ; 

__attribute__((used)) static inline int fdfs_server_info_to_string(const TrackerServerInfo *pServer,
        char *buff, const int buffSize)
{
    return fdfs_server_info_to_string_ex(pServer,
            pServer->connections[0].port, buff, buffSize);
}