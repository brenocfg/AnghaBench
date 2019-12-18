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
struct x509_pm {unsigned char* x509_crt; } ;
typedef  int /*<<< orphan*/  mbedtls_x509_crt ;
struct TYPE_3__ {scalar_t__ x509_pm; } ;
typedef  TYPE_1__ X509 ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_DEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SSL_PLATFORM_ERROR_LEVEL ; 
 int /*<<< orphan*/  mbedtls_x509_crt_free (unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_x509_crt_init (unsigned char*) ; 
 int mbedtls_x509_crt_parse (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  ssl_mem_free (unsigned char*) ; 
 void* ssl_mem_malloc (int) ; 
 int /*<<< orphan*/  ssl_memcpy (unsigned char*,unsigned char const*,int) ; 

int x509_pm_load(X509 *x, const unsigned char *buffer, int len)
{
    int ret;
    unsigned char *load_buf;
    struct x509_pm *x509_pm = (struct x509_pm *)x->x509_pm;

	if (x509_pm->x509_crt)
        mbedtls_x509_crt_free(x509_pm->x509_crt);

    if (!x509_pm->x509_crt) {
        x509_pm->x509_crt = ssl_mem_malloc(sizeof(mbedtls_x509_crt));
        if (!x509_pm->x509_crt) {
            SSL_DEBUG(SSL_PLATFORM_ERROR_LEVEL, "no enough memory > (x509_pm->x509_crt)");
            goto no_mem;
        }
    }

    load_buf = ssl_mem_malloc(len + 1);
    if (!load_buf) {
        SSL_DEBUG(SSL_PLATFORM_ERROR_LEVEL, "no enough memory > (load_buf)");
        goto failed;
    }

    ssl_memcpy(load_buf, buffer, len);
    load_buf[len] = '\0';

    mbedtls_x509_crt_init(x509_pm->x509_crt);

    ret = mbedtls_x509_crt_parse(x509_pm->x509_crt, load_buf, len + 1);
    ssl_mem_free(load_buf);

    if (ret) {
        SSL_DEBUG(SSL_PLATFORM_ERROR_LEVEL, "mbedtls_x509_crt_parse return -0x%x", -ret);
        goto failed;
    }

    return 0;

failed:
    mbedtls_x509_crt_free(x509_pm->x509_crt);
    ssl_mem_free(x509_pm->x509_crt);
    x509_pm->x509_crt = NULL;
no_mem:
    return -1;
}