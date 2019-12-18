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
struct TYPE_8__ {int ref_counter; int /*<<< orphan*/  method; } ;
typedef  TYPE_1__ X509 ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_DEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SSL_PKEY_ERROR_LEVEL ; 
 int /*<<< orphan*/  SSL_X509_ERROR_LEVEL ; 
 int X509_METHOD_CALL (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  X509_method () ; 
 int /*<<< orphan*/  new ; 
 int /*<<< orphan*/  ssl_mem_free (TYPE_1__*) ; 
 TYPE_1__* ssl_mem_zalloc (int) ; 

X509* __X509_new(X509 *ix)
{
    int ret;
    X509 *x;

    x = ssl_mem_zalloc(sizeof(X509));
    if (!x) {
        SSL_DEBUG(SSL_X509_ERROR_LEVEL, "no enough memory > (x)");
        goto no_mem;
    }

    x->ref_counter = 1;

    if (ix)
        x->method = ix->method;
    else
        x->method = X509_method();

    ret = X509_METHOD_CALL(new, x, ix);
    if (ret) {
        SSL_DEBUG(SSL_PKEY_ERROR_LEVEL, "X509_METHOD_CALL(new) return %d", ret);
        goto failed;
    }

    return x;

failed:
    ssl_mem_free(x);
no_mem:
    return NULL;
}