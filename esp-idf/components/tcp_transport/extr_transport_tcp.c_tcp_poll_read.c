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
typedef  int uint32_t ;
struct TYPE_3__ {scalar_t__ sock; } ;
typedef  TYPE_1__ transport_tcp_t ;
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  sock_errno ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  esp_transport_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ FD_ISSET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ERROR ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_1__* esp_transport_get_context_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_transport_utils_ms_to_timeval (int,struct timeval*) ; 
 int /*<<< orphan*/  getsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static int tcp_poll_read(esp_transport_handle_t t, int timeout_ms)
{
    transport_tcp_t *tcp = esp_transport_get_context_data(t);
    int ret = -1;
    fd_set readset;
    fd_set errset;
    FD_ZERO(&readset);
    FD_ZERO(&errset);
    FD_SET(tcp->sock, &readset);
    FD_SET(tcp->sock, &errset);
    struct timeval timeout;
    esp_transport_utils_ms_to_timeval(timeout_ms, &timeout);
    ret = select(tcp->sock + 1, &readset, NULL, &errset, &timeout);
    if (ret > 0 && FD_ISSET(tcp->sock, &errset)) {
        int sock_errno = 0;
        uint32_t optlen = sizeof(sock_errno);
        getsockopt(tcp->sock, SOL_SOCKET, SO_ERROR, &sock_errno, &optlen);
        ESP_LOGE(TAG, "tcp_poll_read select error %d, errno = %s, fd = %d", sock_errno, strerror(sock_errno), tcp->sock);
        ret = -1;
    }
    return ret;
}