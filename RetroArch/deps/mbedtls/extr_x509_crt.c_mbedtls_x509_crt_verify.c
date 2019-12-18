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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  mbedtls_x509_crt ;
typedef  int /*<<< orphan*/  mbedtls_x509_crl ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_x509_crt_profile_default ; 
 int mbedtls_x509_crt_verify_with_profile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int (*) (void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *),void*) ; 

int mbedtls_x509_crt_verify( mbedtls_x509_crt *crt,
                     mbedtls_x509_crt *trust_ca,
                     mbedtls_x509_crl *ca_crl,
                     const char *cn, uint32_t *flags,
                     int (*f_vrfy)(void *, mbedtls_x509_crt *, int, uint32_t *),
                     void *p_vrfy )
{
    return( mbedtls_x509_crt_verify_with_profile( crt, trust_ca, ca_crl,
                &mbedtls_x509_crt_profile_default, cn, flags, f_vrfy, p_vrfy ) );
}