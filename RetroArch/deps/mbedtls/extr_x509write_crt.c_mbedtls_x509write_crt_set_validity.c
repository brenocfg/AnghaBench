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
struct TYPE_3__ {char* not_before; char* not_after; } ;
typedef  TYPE_1__ mbedtls_x509write_cert ;

/* Variables and functions */
 int MBEDTLS_ERR_X509_BAD_INPUT_DATA ; 
 int MBEDTLS_X509_RFC5280_UTC_TIME_LEN ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

int mbedtls_x509write_crt_set_validity( mbedtls_x509write_cert *ctx, const char *not_before,
                                const char *not_after )
{
    if( strlen( not_before ) != MBEDTLS_X509_RFC5280_UTC_TIME_LEN - 1 ||
        strlen( not_after )  != MBEDTLS_X509_RFC5280_UTC_TIME_LEN - 1 )
    {
        return( MBEDTLS_ERR_X509_BAD_INPUT_DATA );
    }
    strncpy( ctx->not_before, not_before, MBEDTLS_X509_RFC5280_UTC_TIME_LEN );
    strncpy( ctx->not_after , not_after , MBEDTLS_X509_RFC5280_UTC_TIME_LEN );
    ctx->not_before[MBEDTLS_X509_RFC5280_UTC_TIME_LEN - 1] = 'Z';
    ctx->not_after[MBEDTLS_X509_RFC5280_UTC_TIME_LEN - 1] = 'Z';

    return( 0 );
}