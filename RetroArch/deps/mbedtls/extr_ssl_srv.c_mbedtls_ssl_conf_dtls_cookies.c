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
typedef  int /*<<< orphan*/  mbedtls_ssl_cookie_write_t ;
typedef  int /*<<< orphan*/  mbedtls_ssl_cookie_check_t ;
struct TYPE_3__ {void* p_cookie; int /*<<< orphan*/ * f_cookie_check; int /*<<< orphan*/ * f_cookie_write; } ;
typedef  TYPE_1__ mbedtls_ssl_config ;

/* Variables and functions */

void mbedtls_ssl_conf_dtls_cookies( mbedtls_ssl_config *conf,
                           mbedtls_ssl_cookie_write_t *f_cookie_write,
                           mbedtls_ssl_cookie_check_t *f_cookie_check,
                           void *p_cookie )
{
    conf->f_cookie_write = f_cookie_write;
    conf->f_cookie_check = f_cookie_check;
    conf->p_cookie       = p_cookie;
}