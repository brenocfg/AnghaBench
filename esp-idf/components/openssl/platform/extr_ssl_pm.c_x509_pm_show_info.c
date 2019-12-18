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
struct x509_pm {int /*<<< orphan*/ * ex_crt; int /*<<< orphan*/ * x509_crt; } ;
typedef  int /*<<< orphan*/  mbedtls_x509_crt ;
struct TYPE_3__ {struct x509_pm* x509_pm; } ;
typedef  TYPE_1__ X509 ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_DEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SSL_DEBUG_ON ; 
 int /*<<< orphan*/  SSL_PLATFORM_ERROR_LEVEL ; 
 scalar_t__ X509_INFO_STRING_LENGTH ; 
 int mbedtls_x509_crt_info (char*,scalar_t__,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_mem_free (char*) ; 
 char* ssl_mem_malloc (scalar_t__) ; 

int x509_pm_show_info(X509 *x)
{
    int ret;
    char *buf;
    mbedtls_x509_crt *x509_crt;
    struct x509_pm *x509_pm = x->x509_pm;

    if (x509_pm->x509_crt)
        x509_crt = x509_pm->x509_crt;
    else if (x509_pm->ex_crt)
        x509_crt = x509_pm->ex_crt;
    else
        x509_crt = NULL;

    if (!x509_crt)
        return -1;

    buf = ssl_mem_malloc(X509_INFO_STRING_LENGTH);
    if (!buf) {
        SSL_DEBUG(SSL_PLATFORM_ERROR_LEVEL, "no enough memory > (buf)");
        goto no_mem;
    }

    ret = mbedtls_x509_crt_info(buf, X509_INFO_STRING_LENGTH - 1, "", x509_crt);
    if (ret <= 0) {
        SSL_DEBUG(SSL_PLATFORM_ERROR_LEVEL, "mbedtls_x509_crt_info() return -0x%x", -ret);
        goto mbedtls_err1;
    }

    buf[ret] = 0;

    ssl_mem_free(buf);

    SSL_DEBUG(SSL_DEBUG_ON, "%s", buf);

    return 0;

mbedtls_err1:
    ssl_mem_free(buf);
no_mem:
    return -1;
}