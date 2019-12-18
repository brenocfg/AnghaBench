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
 int /*<<< orphan*/  COMP_LEAK_GENERAL ; 
 int /*<<< orphan*/  COMP_LEAK_LWIP ; 
 int CONFIG_LWIP_MAX_SOCKETS ; 
 int /*<<< orphan*/  CONFIG_UNITY_CRITICAL_LEAK_LEVEL_LWIP ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int PF_INET ; 
 int PF_INET6 ; 
 int SOCK_DGRAM ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  TYPE_LEAK_CRITICAL ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  esp_netif_init () ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  printf (char*) ; 
 int socket (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_utils_set_leak_level (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unity_reset_leak_checks () ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

void test_case_uses_tcpip(void)
{
    // Can be called more than once, does nothing on subsequent calls
    esp_netif_init();

    // Allocate all sockets then free them
    // (First time each socket is allocated some one-time allocations happen.)
    int sockets[CONFIG_LWIP_MAX_SOCKETS];
    for (int i = 0; i < CONFIG_LWIP_MAX_SOCKETS; i++) {
        int type = (i % 2 == 0) ? SOCK_DGRAM : SOCK_STREAM;
        int family = (i % 3 == 0) ? PF_INET6 : PF_INET;
        sockets[i] = socket(family, type, IPPROTO_IP);
    }
    for (int i = 0; i < CONFIG_LWIP_MAX_SOCKETS; i++) {
        close(sockets[i]);
    }

    // Allow LWIP tasks to finish initialising themselves
    vTaskDelay(25 / portTICK_RATE_MS);

    printf("Note: esp_netif_init() has been called. Until next reset, TCP/IP task will periodicially allocate memory and consume CPU time.\n");

    // Reset the leak checker as LWIP allocates a lot of memory on first run
    unity_reset_leak_checks();
    test_utils_set_leak_level(0, TYPE_LEAK_CRITICAL, COMP_LEAK_GENERAL);
    test_utils_set_leak_level(CONFIG_UNITY_CRITICAL_LEAK_LEVEL_LWIP, TYPE_LEAK_CRITICAL, COMP_LEAK_LWIP);
}