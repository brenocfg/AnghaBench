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
 int FDFS_TRACKER_SERVER_DEF_PORT ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 

__attribute__((used)) static void usage(char *argv[])
{
	printf("Usage: %s <config_file> [-h <tracker_server>] "
            "[list|delete|set_trunk_server <group_name> [storage_id]]\n"
            "\tthe tracker server format: host[:port], "
            "the tracker default port is %d\n\n",
            argv[0], FDFS_TRACKER_SERVER_DEF_PORT);
}