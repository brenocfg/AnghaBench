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
typedef  float uint32_t ;
typedef  int /*<<< orphan*/  transmitted ;
typedef  int /*<<< orphan*/  total_time_ms ;
typedef  int /*<<< orphan*/  target_addr ;
typedef  int /*<<< orphan*/  received ;
typedef  float ip_addr_t ;
typedef  int /*<<< orphan*/  esp_ping_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_PING_PROF_DURATION ; 
 int /*<<< orphan*/  ESP_PING_PROF_IPADDR ; 
 int /*<<< orphan*/  ESP_PING_PROF_REPLY ; 
 int /*<<< orphan*/  ESP_PING_PROF_REQUEST ; 
 scalar_t__ IP_IS_V4 (float*) ; 
 int /*<<< orphan*/  esp_ping_delete_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_ping_get_profile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*,int) ; 
 char* inet6_ntoa (int /*<<< orphan*/ ) ; 
 char* inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ip_2_ip4 (float*) ; 
 int /*<<< orphan*/ * ip_2_ip6 (float*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void cmd_ping_on_ping_end(esp_ping_handle_t hdl, void *args)
{
    ip_addr_t target_addr;
    uint32_t transmitted;
    uint32_t received;
    uint32_t total_time_ms;
    esp_ping_get_profile(hdl, ESP_PING_PROF_REQUEST, &transmitted, sizeof(transmitted));
    esp_ping_get_profile(hdl, ESP_PING_PROF_REPLY, &received, sizeof(received));
    esp_ping_get_profile(hdl, ESP_PING_PROF_IPADDR, &target_addr, sizeof(target_addr));
    esp_ping_get_profile(hdl, ESP_PING_PROF_DURATION, &total_time_ms, sizeof(total_time_ms));
    uint32_t loss = (uint32_t)((1 - ((float)received) / transmitted) * 100);
    if (IP_IS_V4(&target_addr)) {
        printf("\n--- %s ping statistics ---\n", inet_ntoa(*ip_2_ip4(&target_addr)));
    } else {
        printf("\n--- %s ping statistics ---\n", inet6_ntoa(*ip_2_ip6(&target_addr)));
    }
    printf("%d packets transmitted, %d received, %d%% packet loss, time %dms\n",
           transmitted, received, loss, total_time_ms);
    // delete the ping sessions, so that we clean up all resources and can create a new ping session
    // we don't have to call delete function in the callback, instead we can call delete function from other tasks
    esp_ping_delete_session(hdl);
}