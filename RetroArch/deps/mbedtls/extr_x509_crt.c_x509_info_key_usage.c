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
 int /*<<< orphan*/  KEY_USAGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MBEDTLS_X509_KU_CRL_SIGN ; 
 int /*<<< orphan*/  MBEDTLS_X509_KU_DATA_ENCIPHERMENT ; 
 int /*<<< orphan*/  MBEDTLS_X509_KU_DECIPHER_ONLY ; 
 int /*<<< orphan*/  MBEDTLS_X509_KU_DIGITAL_SIGNATURE ; 
 int /*<<< orphan*/  MBEDTLS_X509_KU_ENCIPHER_ONLY ; 
 int /*<<< orphan*/  MBEDTLS_X509_KU_KEY_AGREEMENT ; 
 int /*<<< orphan*/  MBEDTLS_X509_KU_KEY_CERT_SIGN ; 
 int /*<<< orphan*/  MBEDTLS_X509_KU_KEY_ENCIPHERMENT ; 
 int /*<<< orphan*/  MBEDTLS_X509_KU_NON_REPUDIATION ; 

__attribute__((used)) static int x509_info_key_usage( char **buf, size_t *size,
                                unsigned int key_usage )
{
    int ret;
    size_t n = *size;
    char *p = *buf;
    const char *sep = "";

    KEY_USAGE( MBEDTLS_X509_KU_DIGITAL_SIGNATURE,    "Digital Signature" );
    KEY_USAGE( MBEDTLS_X509_KU_NON_REPUDIATION,      "Non Repudiation" );
    KEY_USAGE( MBEDTLS_X509_KU_KEY_ENCIPHERMENT,     "Key Encipherment" );
    KEY_USAGE( MBEDTLS_X509_KU_DATA_ENCIPHERMENT,    "Data Encipherment" );
    KEY_USAGE( MBEDTLS_X509_KU_KEY_AGREEMENT,        "Key Agreement" );
    KEY_USAGE( MBEDTLS_X509_KU_KEY_CERT_SIGN,        "Key Cert Sign" );
    KEY_USAGE( MBEDTLS_X509_KU_CRL_SIGN,             "CRL Sign" );
    KEY_USAGE( MBEDTLS_X509_KU_ENCIPHER_ONLY,        "Encipher Only" );
    KEY_USAGE( MBEDTLS_X509_KU_DECIPHER_ONLY,        "Decipher Only" );

    *size = n;
    *buf = p;

    return( 0 );
}