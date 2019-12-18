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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int) ; 
 int tipc_cluster (int /*<<< orphan*/ ) ; 
 int tipc_node (int /*<<< orphan*/ ) ; 
 int tipc_zone (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline char *addr_string_fill(char *string, u32 addr)
{
	snprintf(string, 16, "<%u.%u.%u>",
		 tipc_zone(addr), tipc_cluster(addr), tipc_node(addr));
	return string;
}