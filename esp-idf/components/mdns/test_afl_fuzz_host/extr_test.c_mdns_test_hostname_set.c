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
typedef  int /*<<< orphan*/  mdns_action_t ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastItem (int /*<<< orphan*/ **) ; 
 int mdns_hostname_set (char const*) ; 
 int /*<<< orphan*/  mdns_test_execute_action (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mdns_test_hostname_set(const char * mdns_hostname)
{
    int ret = mdns_hostname_set(mdns_hostname);
    mdns_action_t * a = NULL;
    GetLastItem(&a);
    mdns_test_execute_action(a);
    return ret;
}