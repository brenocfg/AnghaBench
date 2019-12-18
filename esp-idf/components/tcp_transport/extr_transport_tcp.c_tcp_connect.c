#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tv ;
struct TYPE_4__ {int sock; } ;
typedef  TYPE_1__ transport_tcp_t ;
struct timeval {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  ip_addr_t ;
typedef  int /*<<< orphan*/  esp_transport_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVTIMEO ; 
 int /*<<< orphan*/  SO_SNDTIMEO ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 TYPE_1__* esp_transport_get_context_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_transport_utils_ms_to_timeval (int,struct timeval*) ; 
 int /*<<< orphan*/  htons (int) ; 
 int inet_pton (int /*<<< orphan*/ ,char const*,TYPE_2__*) ; 
 int /*<<< orphan*/  ipaddr_ntoa (int /*<<< orphan*/  const*) ; 
 scalar_t__ resolve_dns (char const*,struct sockaddr_in*) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcp_connect(esp_transport_handle_t t, const char *host, int port, int timeout_ms)
{
    struct sockaddr_in remote_ip;
    struct timeval tv;
    transport_tcp_t *tcp = esp_transport_get_context_data(t);

    bzero(&remote_ip, sizeof(struct sockaddr_in));

    //if stream_host is not ip address, resolve it AF_INET,servername,&serveraddr.sin_addr
    if (inet_pton(AF_INET, host, &remote_ip.sin_addr) != 1) {
        if (resolve_dns(host, &remote_ip) < 0) {
            return -1;
        }
    }

    tcp->sock = socket(PF_INET, SOCK_STREAM, 0);

    if (tcp->sock < 0) {
        ESP_LOGE(TAG, "Error create socket");
        return -1;
    }

    remote_ip.sin_family = AF_INET;
    remote_ip.sin_port = htons(port);

    esp_transport_utils_ms_to_timeval(timeout_ms, &tv);

    setsockopt(tcp->sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    setsockopt(tcp->sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));

    ESP_LOGD(TAG, "[sock=%d],connecting to server IP:%s,Port:%d...",
             tcp->sock, ipaddr_ntoa((const ip_addr_t*)&remote_ip.sin_addr.s_addr), port);
    if (connect(tcp->sock, (struct sockaddr *)(&remote_ip), sizeof(struct sockaddr)) != 0) {
        close(tcp->sock);
        tcp->sock = -1;
        return -1;
    }
    return tcp->sock;
}