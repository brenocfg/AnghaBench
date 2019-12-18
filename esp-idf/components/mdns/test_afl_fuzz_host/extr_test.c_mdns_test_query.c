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
typedef  int /*<<< orphan*/  mdns_result_t ;
typedef  int /*<<< orphan*/  mdns_action_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_SEARCH_ADD ; 
 int /*<<< orphan*/  GetLastItem (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  MDNS_TYPE_PTR ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  mdns_test_execute_action (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdns_test_search_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdns_test_search_init (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ mdns_test_send_search_action (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  search ; 

__attribute__((used)) static mdns_result_t* mdns_test_query(const char * service_name, const char * proto)
{
    search = mdns_test_search_init(NULL, service_name, proto, MDNS_TYPE_PTR, 3000, 20);
    if (!search) {
        abort();
    }

    if (mdns_test_send_search_action(ACTION_SEARCH_ADD, search)) {
        mdns_test_search_free(search);
        abort();
    }

    mdns_action_t * a = NULL;
    GetLastItem(&a);
    mdns_test_execute_action(a);
    return NULL;
}