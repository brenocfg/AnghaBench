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
 int /*<<< orphan*/  register_mdns_free () ; 
 int /*<<< orphan*/  register_mdns_init () ; 
 int /*<<< orphan*/  register_mdns_query_a () ; 
 int /*<<< orphan*/  register_mdns_query_aaaa () ; 
 int /*<<< orphan*/  register_mdns_query_ip () ; 
 int /*<<< orphan*/  register_mdns_query_ptr () ; 
 int /*<<< orphan*/  register_mdns_query_srv () ; 
 int /*<<< orphan*/  register_mdns_query_svc () ; 
 int /*<<< orphan*/  register_mdns_query_txt () ; 
 int /*<<< orphan*/  register_mdns_service_add () ; 
 int /*<<< orphan*/  register_mdns_service_instance_set () ; 
 int /*<<< orphan*/  register_mdns_service_port_set () ; 
 int /*<<< orphan*/  register_mdns_service_remove () ; 
 int /*<<< orphan*/  register_mdns_service_remove_all () ; 
 int /*<<< orphan*/  register_mdns_service_txt_remove () ; 
 int /*<<< orphan*/  register_mdns_service_txt_replace () ; 
 int /*<<< orphan*/  register_mdns_service_txt_set () ; 
 int /*<<< orphan*/  register_mdns_set_hostname () ; 
 int /*<<< orphan*/  register_mdns_set_instance () ; 

void mdns_console_register(void)
{
    register_mdns_init();
    register_mdns_free();
    register_mdns_set_hostname();
    register_mdns_set_instance();
    register_mdns_service_add();
    register_mdns_service_remove();
    register_mdns_service_instance_set();
    register_mdns_service_port_set();
    register_mdns_service_txt_replace();
    register_mdns_service_txt_set();
    register_mdns_service_txt_remove();
    register_mdns_service_remove_all();

    register_mdns_query_a();
    register_mdns_query_aaaa();
    register_mdns_query_txt();
    register_mdns_query_srv();
    register_mdns_query_ptr();

    register_mdns_query_ip();
    register_mdns_query_svc();
}