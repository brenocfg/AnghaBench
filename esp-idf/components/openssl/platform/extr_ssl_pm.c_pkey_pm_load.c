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
struct pkey_pm {unsigned char* pkey; } ;
typedef  int /*<<< orphan*/  mbedtls_pk_context ;
struct TYPE_3__ {scalar_t__ pkey_pm; } ;
typedef  TYPE_1__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_DEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SSL_PLATFORM_ERROR_LEVEL ; 
 int /*<<< orphan*/  mbedtls_pk_free (unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_pk_init (unsigned char*) ; 
 int mbedtls_pk_parse_key (unsigned char*,unsigned char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_mem_free (unsigned char*) ; 
 void* ssl_mem_malloc (int) ; 
 int /*<<< orphan*/  ssl_memcpy (unsigned char*,unsigned char const*,int) ; 

int pkey_pm_load(EVP_PKEY *pk, const unsigned char *buffer, int len)
{
    int ret;
    unsigned char *load_buf;
    struct pkey_pm *pkey_pm = (struct pkey_pm *)pk->pkey_pm;

    if (pkey_pm->pkey)
        mbedtls_pk_free(pkey_pm->pkey);

    if (!pkey_pm->pkey) {
        pkey_pm->pkey = ssl_mem_malloc(sizeof(mbedtls_pk_context));
        if (!pkey_pm->pkey) {
            SSL_DEBUG(SSL_PLATFORM_ERROR_LEVEL, "no enough memory > (pkey_pm->pkey)");
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

    mbedtls_pk_init(pkey_pm->pkey);

    ret = mbedtls_pk_parse_key(pkey_pm->pkey, load_buf, len + 1, NULL, 0);
    ssl_mem_free(load_buf);

    if (ret) {
        SSL_DEBUG(SSL_PLATFORM_ERROR_LEVEL, "mbedtls_pk_parse_key return -0x%x", -ret);
        goto failed;
    }

    return 0;

failed:
    mbedtls_pk_free(pkey_pm->pkey);
    ssl_mem_free(pkey_pm->pkey);
    pkey_pm->pkey = NULL;
no_mem:
    return -1;
}