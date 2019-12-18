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
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_3__ {int /*<<< orphan*/  dlen; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_ASSERT2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_DEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SSL_PKEY_ERROR_LEVEL ; 
 int X509_METHOD_CALL (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_new () ; 
 int /*<<< orphan*/  load ; 

X509 * PEM_read_bio_X509(BIO *bp, X509 **cert, void *cb, void *u) {
    int m = 0;
    int ret;
    X509 *x;

    SSL_ASSERT2(bp->data);
    SSL_ASSERT2(bp->dlen);

    if (cert && *cert) {
        x = *cert;
    } else {
        x = X509_new();
        if (!x) {
            SSL_DEBUG(SSL_PKEY_ERROR_LEVEL, "X509_new() return NULL");
            goto failed;
        }
        m = 1;
    }

    ret = X509_METHOD_CALL(load, x, bp->data, bp->dlen);
    if (ret) {
        SSL_DEBUG(SSL_PKEY_ERROR_LEVEL, "X509_METHOD_CALL(load) return %d", ret);
        goto failed;
    }

    return x;

failed:
    if (m) {
        X509_free(x);
    }

    return NULL;
}