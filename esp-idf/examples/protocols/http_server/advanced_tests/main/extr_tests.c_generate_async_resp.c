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
struct async_resp_arg {int fd; int /*<<< orphan*/  hd; } ;
typedef  int /*<<< orphan*/  httpd_handle_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int) ; 
 char* HTTPD_HDR_STR ; 
 char* STR ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  httpd_default_send (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void generate_async_resp(void *arg)
{
    char buf[250];
    struct async_resp_arg *resp_arg = (struct async_resp_arg *)arg;
    httpd_handle_t hd = resp_arg->hd;
    int fd = resp_arg->fd;
#define HTTPD_HDR_STR      "HTTP/1.1 200 OK\r\n"                   \
                           "Content-Type: text/html\r\n"           \
                           "Content-Length: %d\r\n"
#define STR "Hello Double World!"

    ESP_LOGI(TAG, "Executing queued work fd : %d", fd);

    snprintf(buf, sizeof(buf), HTTPD_HDR_STR,
         strlen(STR));
    httpd_default_send(hd, fd, buf, strlen(buf), 0);
    /* Space for sending additional headers based on set_header */
    httpd_default_send(hd, fd, "\r\n", strlen("\r\n"), 0);
    httpd_default_send(hd, fd, STR, strlen(STR), 0);
#undef STR
    free(arg);
}