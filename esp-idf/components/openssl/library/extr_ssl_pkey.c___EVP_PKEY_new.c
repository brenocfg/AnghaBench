#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  method; } ;
typedef  TYPE_1__ EVP_PKEY ;

/* Variables and functions */
 int EVP_PKEY_METHOD_CALL (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  EVP_PKEY_method () ; 
 int /*<<< orphan*/  SSL_DEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SSL_PKEY_ERROR_LEVEL ; 
 int /*<<< orphan*/  new ; 
 int /*<<< orphan*/  ssl_mem_free (TYPE_1__*) ; 
 TYPE_1__* ssl_mem_zalloc (int) ; 

EVP_PKEY* __EVP_PKEY_new(EVP_PKEY *ipk)
{
    int ret;
    EVP_PKEY *pkey;

    pkey = ssl_mem_zalloc(sizeof(EVP_PKEY));
    if (!pkey) {
        SSL_DEBUG(SSL_PKEY_ERROR_LEVEL, "no enough memory > (pkey)");
        goto no_mem;
    }

    if (ipk) {
        pkey->method = ipk->method;
    } else {
        pkey->method = EVP_PKEY_method();
    }

    ret = EVP_PKEY_METHOD_CALL(new, pkey, ipk);
    if (ret) {
        SSL_DEBUG(SSL_PKEY_ERROR_LEVEL, "EVP_PKEY_METHOD_CALL(new) return %d", ret);
        goto failed;
    }

    return pkey;

failed:
    ssl_mem_free(pkey);
no_mem:
    return NULL;
}