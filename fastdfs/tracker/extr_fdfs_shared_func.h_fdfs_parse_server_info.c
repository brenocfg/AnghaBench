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

/* Variables and functions */
 int fdfs_parse_server_info_ex (char*,int const,int /*<<< orphan*/ *,int const) ; 

__attribute__((used)) static inline int fdfs_parse_server_info(char *server_str, const int default_port,
        TrackerServerInfo *pServer)
{
    const bool resolve = true;
    return fdfs_parse_server_info_ex(server_str, default_port,
            pServer, resolve);
}