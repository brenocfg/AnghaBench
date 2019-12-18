#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  serviceTxtData ;
struct TYPE_3__ {char* member_0; char* member_1; } ;
typedef  TYPE_1__ mdns_txt_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_EXAMPLE_MDNS_HOST_NAME ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDNS_INSTANCE ; 
 int /*<<< orphan*/  mdns_hostname_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdns_init () ; 
 int /*<<< orphan*/  mdns_instance_name_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdns_service_add (char*,char*,char*,int,TYPE_1__*,int) ; 

__attribute__((used)) static void initialise_mdns(void)
{
    mdns_init();
    mdns_hostname_set(CONFIG_EXAMPLE_MDNS_HOST_NAME);
    mdns_instance_name_set(MDNS_INSTANCE);

    mdns_txt_item_t serviceTxtData[] = {
        {"board", "esp32"},
        {"path", "/"}
    };

    ESP_ERROR_CHECK(mdns_service_add("ESP32-WebServer", "_http", "_tcp", 80, serviceTxtData,
                                     sizeof(serviceTxtData) / sizeof(serviceTxtData[0])));
}