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

/* Variables and functions */
 int /*<<< orphan*/  CERT_TYPE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MBEDTLS_X509_NS_CERT_TYPE_EMAIL ; 
 int /*<<< orphan*/  MBEDTLS_X509_NS_CERT_TYPE_EMAIL_CA ; 
 int /*<<< orphan*/  MBEDTLS_X509_NS_CERT_TYPE_OBJECT_SIGNING ; 
 int /*<<< orphan*/  MBEDTLS_X509_NS_CERT_TYPE_OBJECT_SIGNING_CA ; 
 int /*<<< orphan*/  MBEDTLS_X509_NS_CERT_TYPE_RESERVED ; 
 int /*<<< orphan*/  MBEDTLS_X509_NS_CERT_TYPE_SSL_CA ; 
 int /*<<< orphan*/  MBEDTLS_X509_NS_CERT_TYPE_SSL_CLIENT ; 
 int /*<<< orphan*/  MBEDTLS_X509_NS_CERT_TYPE_SSL_SERVER ; 

__attribute__((used)) static int x509_info_cert_type( char **buf, size_t *size,
                                unsigned char ns_cert_type )
{
    int ret;
    size_t n = *size;
    char *p = *buf;
    const char *sep = "";

    CERT_TYPE( MBEDTLS_X509_NS_CERT_TYPE_SSL_CLIENT,         "SSL Client" );
    CERT_TYPE( MBEDTLS_X509_NS_CERT_TYPE_SSL_SERVER,         "SSL Server" );
    CERT_TYPE( MBEDTLS_X509_NS_CERT_TYPE_EMAIL,              "Email" );
    CERT_TYPE( MBEDTLS_X509_NS_CERT_TYPE_OBJECT_SIGNING,     "Object Signing" );
    CERT_TYPE( MBEDTLS_X509_NS_CERT_TYPE_RESERVED,           "Reserved" );
    CERT_TYPE( MBEDTLS_X509_NS_CERT_TYPE_SSL_CA,             "SSL CA" );
    CERT_TYPE( MBEDTLS_X509_NS_CERT_TYPE_EMAIL_CA,           "Email CA" );
    CERT_TYPE( MBEDTLS_X509_NS_CERT_TYPE_OBJECT_SIGNING_CA,  "Object Signing CA" );

    *size = n;
    *buf = p;

    return( 0 );
}