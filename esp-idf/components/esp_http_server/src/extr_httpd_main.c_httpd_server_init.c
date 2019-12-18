#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct in6_addr {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; struct in6_addr sin6_addr; int /*<<< orphan*/  sin6_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl_port; int /*<<< orphan*/  backlog_conn; int /*<<< orphan*/  server_port; } ;
struct httpd_data {int listen_fd; int ctrl_fd; int msg_fd; TYPE_1__ config; } ;
typedef  int /*<<< orphan*/  serv_addr ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  enable ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_OK ; 
 struct in6_addr IN6ADDR_ANY_INIT ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  TAG ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int cs_create_ctrl_sock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int listen (int,int /*<<< orphan*/ ) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t httpd_server_init(struct httpd_data *hd)
{
    int fd = socket(PF_INET6, SOCK_STREAM, 0);
    if (fd < 0) {
        ESP_LOGE(TAG, LOG_FMT("error in socket (%d)"), errno);
        return ESP_FAIL;
    }

    struct in6_addr inaddr_any = IN6ADDR_ANY_INIT;
    struct sockaddr_in6 serv_addr = {
        .sin6_family  = PF_INET6,
        .sin6_addr    = inaddr_any,
        .sin6_port    = htons(hd->config.server_port)
    };

    /* Enable SO_REUSEADDR to allow binding to the same
     * address and port when restarting the server */
    int enable = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0) {
        /* This will fail if CONFIG_LWIP_SO_REUSE is not enabled. But
         * it does not affect the normal working of the HTTP Server */
        ESP_LOGW(TAG, LOG_FMT("error enabling SO_REUSEADDR (%d)"), errno);
    }

    int ret = bind(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret < 0) {
        ESP_LOGE(TAG, LOG_FMT("error in bind (%d)"), errno);
        close(fd);
        return ESP_FAIL;
    }

    ret = listen(fd, hd->config.backlog_conn);
    if (ret < 0) {
        ESP_LOGE(TAG, LOG_FMT("error in listen (%d)"), errno);
        close(fd);
        return ESP_FAIL;
    }

    int ctrl_fd = cs_create_ctrl_sock(hd->config.ctrl_port);
    if (ctrl_fd < 0) {
        ESP_LOGE(TAG, LOG_FMT("error in creating ctrl socket (%d)"), errno);
        close(fd);
        return ESP_FAIL;
    }

    int msg_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (msg_fd < 0) {
        ESP_LOGE(TAG, LOG_FMT("error in creating msg socket (%d)"), errno);
        close(fd);
        close(ctrl_fd);
        return ESP_FAIL;
    }

    hd->listen_fd = fd;
    hd->ctrl_fd = ctrl_fd;
    hd->msg_fd  = msg_fd;
    return ESP_OK;
}