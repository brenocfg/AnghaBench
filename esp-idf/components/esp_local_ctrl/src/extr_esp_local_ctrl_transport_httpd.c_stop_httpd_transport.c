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
typedef  int /*<<< orphan*/  protocomm_t ;

/* Variables and functions */
 int /*<<< orphan*/  httpd_ssl_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdns_service_remove (char*,char*) ; 
 int /*<<< orphan*/  protocomm_httpd_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * server_handle ; 

__attribute__((used)) static void stop_httpd_transport(protocomm_t *pc)
{
    mdns_service_remove("_esp_local_ctrl", "_tcp");
    protocomm_httpd_stop(pc);
    httpd_ssl_stop(server_handle);
    server_handle = NULL;
}