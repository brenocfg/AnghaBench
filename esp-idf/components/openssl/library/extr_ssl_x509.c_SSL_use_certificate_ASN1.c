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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_DEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SSL_PKEY_ERROR_LEVEL ; 
 int SSL_use_certificate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_X509 (int /*<<< orphan*/ *,unsigned char const*,int) ; 

int SSL_use_certificate_ASN1(SSL *ssl, int len,
                             const unsigned char *d)
{
    int ret;
    X509 *x;

    x = d2i_X509(NULL, d, len);
    if (!x) {
        SSL_DEBUG(SSL_PKEY_ERROR_LEVEL, "d2i_X509() return NULL");
        goto failed1;
    }

    ret = SSL_use_certificate(ssl, x);
    if (!ret) {
        SSL_DEBUG(SSL_PKEY_ERROR_LEVEL, "SSL_use_certificate() return %d", ret);
        goto failed2;
    }

    return 1;

failed2:
    X509_free(x);
failed1:
    return 0;
}