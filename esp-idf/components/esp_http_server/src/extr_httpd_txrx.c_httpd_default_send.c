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
typedef  int /*<<< orphan*/  httpd_handle_t ;

/* Variables and functions */
 int HTTPD_SOCK_ERR_INVALID ; 
 int httpd_sock_err (char*,int) ; 
 int send (int,char const*,size_t,int) ; 

int httpd_default_send(httpd_handle_t hd, int sockfd, const char *buf, size_t buf_len, int flags)
{
    (void)hd;
    if (buf == NULL) {
        return HTTPD_SOCK_ERR_INVALID;
    }

    int ret = send(sockfd, buf, buf_len, flags);
    if (ret < 0) {
        return httpd_sock_err("send", sockfd);
    }
    return ret;
}