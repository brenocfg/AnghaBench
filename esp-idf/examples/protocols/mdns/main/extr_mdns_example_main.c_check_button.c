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
 int /*<<< orphan*/  EXAMPLE_BUTTON_GPIO ; 
 int gpio_get_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  query_mdns_host (char*) ; 
 int /*<<< orphan*/  query_mdns_service (char*,char*) ; 

__attribute__((used)) static void check_button(void)
{
    static bool old_level = true;
    bool new_level = gpio_get_level(EXAMPLE_BUTTON_GPIO);
    if (!new_level && old_level) {
        query_mdns_host("esp32");
        query_mdns_service("_arduino", "_tcp");
        query_mdns_service("_http", "_tcp");
        query_mdns_service("_printer", "_tcp");
        query_mdns_service("_ipp", "_tcp");
        query_mdns_service("_afpovertcp", "_tcp");
        query_mdns_service("_smb", "_tcp");
        query_mdns_service("_ftp", "_tcp");
        query_mdns_service("_nfs", "_tcp");
    }
    old_level = new_level;
}