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
typedef  int uint32_t ;
struct x509_crt_verify_string {int code; int /*<<< orphan*/ * string; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_X509_SAFE_SNPRINTF ; 
 int mbedtls_snprintf (char*,size_t,char*,char const*,...) ; 
 struct x509_crt_verify_string* x509_crt_verify_strings ; 

int mbedtls_x509_crt_verify_info( char *buf, size_t size, const char *prefix,
                          uint32_t flags )
{
    int ret;
    const struct x509_crt_verify_string *cur;
    char *p = buf;
    size_t n = size;

    for( cur = x509_crt_verify_strings; cur->string != NULL ; cur++ )
    {
        if( ( flags & cur->code ) == 0 )
            continue;

        ret = mbedtls_snprintf( p, n, "%s%s\n", prefix, cur->string );
        MBEDTLS_X509_SAFE_SNPRINTF;
        flags ^= cur->code;
    }

    if( flags != 0 )
    {
        ret = mbedtls_snprintf( p, n, "%sUnknown reason "
                                       "(this should not happen)\n", prefix );
        MBEDTLS_X509_SAFE_SNPRINTF;
    }

    return( (int) ( size - n ) );
}