#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_7__ {TYPE_1__ sin6; } ;
struct TYPE_8__ {scalar_t__ family; TYPE_2__ sa; int /*<<< orphan*/  addr_str_len; int /*<<< orphan*/  port; } ;
typedef  TYPE_3__ apr_sockaddr_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 scalar_t__ APR_INET6 ; 
 int /*<<< orphan*/  IN6_IS_ADDR_V4MAPPED (int /*<<< orphan*/ *) ; 
 char* NUM_BUF_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ apr_sockaddr_ip_getbuf (char*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 char* conv_10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,char*,int*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *conv_apr_sockaddr(apr_sockaddr_t *sa, char *buf_end, apr_size_t *len)
{
    char *p = buf_end;
    int is_negative;
    apr_size_t sub_len;
    char *ipaddr_str;

    p = conv_10(sa->port, TRUE, &is_negative, p, &sub_len);
    *--p = ':';
    ipaddr_str = buf_end - NUM_BUF_SIZE;
    if (apr_sockaddr_ip_getbuf(ipaddr_str, sa->addr_str_len, sa)) {
        /* Should only fail if the buffer is too small, which it
         * should not be; but fail safe anyway: */
        *--p = '?';
        *len = buf_end - p;
        return p;
    }
    sub_len = strlen(ipaddr_str);
#if APR_HAVE_IPV6
    if (sa->family == APR_INET6 &&
        !IN6_IS_ADDR_V4MAPPED(&sa->sa.sin6.sin6_addr)) {
        *(p - 1) = ']';
        p -= sub_len + 2;
        *p = '[';
        memcpy(p + 1, ipaddr_str, sub_len);
    }
    else
#endif
    {
        p -= sub_len;
        memcpy(p, ipaddr_str, sub_len);
    }

    *len = buf_end - p;
    return (p);
}