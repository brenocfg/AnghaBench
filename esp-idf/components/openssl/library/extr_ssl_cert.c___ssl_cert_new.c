#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_6__ {int /*<<< orphan*/ * pkey; int /*<<< orphan*/ * x509; } ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  TYPE_1__ CERT ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CERT_ERROR_LEVEL ; 
 int /*<<< orphan*/  SSL_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * __EVP_PKEY_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * __X509_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_mem_free (TYPE_1__*) ; 
 TYPE_1__* ssl_mem_zalloc (int) ; 

CERT *__ssl_cert_new(CERT *ic)
{
    CERT *cert;

    X509 *ix;
    EVP_PKEY *ipk;

    cert = ssl_mem_zalloc(sizeof(CERT));
    if (!cert) {
        SSL_DEBUG(SSL_CERT_ERROR_LEVEL, "no enough memory > (cert)");
        goto no_mem;
    }

    if (ic) {
        ipk = ic->pkey;
        ix = ic->x509;
    } else {
        ipk = NULL;
        ix = NULL;
    }

    cert->pkey = __EVP_PKEY_new(ipk);
    if (!cert->pkey) {
        SSL_DEBUG(SSL_CERT_ERROR_LEVEL, "__EVP_PKEY_new() return NULL");
        goto pkey_err;
    }

    cert->x509 = __X509_new(ix);
    if (!cert->x509) {
        SSL_DEBUG(SSL_CERT_ERROR_LEVEL, "__X509_new() return NULL");
        goto x509_err;
    }

    return cert;

x509_err:
    EVP_PKEY_free(cert->pkey);
pkey_err:
    ssl_mem_free(cert);
no_mem:
    return NULL;
}