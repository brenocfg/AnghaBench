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
 int /*<<< orphan*/  check_button () ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  query_mdns_host (char*) ; 
 int /*<<< orphan*/  query_mdns_host_with_getaddrinfo (char*) ; 
 int /*<<< orphan*/  query_mdns_host_with_gethostbyname (char*) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void mdns_example_task(void *pvParameters)
{
#if CONFIG_MDNS_RESOLVE_TEST_SERVICES == 1
    /* Send initial queries that are started by CI tester */
    query_mdns_host("tinytester");
    query_mdns_host_with_gethostbyname("tinytester-lwip.local");
    query_mdns_host_with_getaddrinfo("tinytester-lwip.local");
#endif

    while(1) {
        check_button();
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}