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
 int /*<<< orphan*/  T_EXPECT_EQ (int,int,char*,char const*,int) ; 
 int /*<<< orphan*/  T_WITH_ERRNO ; 

__attribute__((used)) static void
expect_special_port_id(int (*fn)(const char *id), int port, const char *portid)
{
	int observed_port = fn(portid);
	T_WITH_ERRNO;
	T_EXPECT_EQ(observed_port, port, "%s is %d", portid, observed_port);
}