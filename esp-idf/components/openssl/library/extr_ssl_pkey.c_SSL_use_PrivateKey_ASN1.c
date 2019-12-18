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
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_DEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SSL_PKEY_ERROR_LEVEL ; 
 int SSL_use_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_PrivateKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char const**,long) ; 

int SSL_use_PrivateKey_ASN1(int type, SSL *ssl,
                                const unsigned char *d, long len)
{
    int ret;
    EVP_PKEY *pk;

    pk = d2i_PrivateKey(0, NULL, &d, len);
    if (!pk) {
        SSL_DEBUG(SSL_PKEY_ERROR_LEVEL, "d2i_PrivateKey() return NULL");
        goto failed1;
    }

    ret = SSL_use_PrivateKey(ssl, pk);
    if (!ret) {
        SSL_DEBUG(SSL_PKEY_ERROR_LEVEL, "SSL_use_PrivateKey() return %d", ret);
        goto failed2;
    }

    return 1;

failed2:
    EVP_PKEY_free(pk);
failed1:
    return 0;
}