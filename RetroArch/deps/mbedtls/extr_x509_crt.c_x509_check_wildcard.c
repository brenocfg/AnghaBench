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
struct TYPE_3__ {int len; char* p; } ;
typedef  TYPE_1__ mbedtls_x509_buf ;

/* Variables and functions */
 size_t strlen (char const*) ; 
 scalar_t__ x509_memcasecmp (char*,char const*,size_t) ; 

__attribute__((used)) static int x509_check_wildcard( const char *cn, mbedtls_x509_buf *name )
{
    size_t i;
    size_t cn_idx = 0, cn_len = strlen( cn );

    if( name->len < 3 || name->p[0] != '*' || name->p[1] != '.' )
        return( 0 );

    for( i = 0; i < cn_len; ++i )
    {
        if( cn[i] == '.' )
        {
            cn_idx = i;
            break;
        }
    }

    if( cn_idx == 0 )
        return( -1 );

    if( cn_len - cn_idx == name->len - 1 &&
        x509_memcasecmp( name->p + 1, cn + cn_idx, name->len - 1 ) == 0 )
    {
        return( 0 );
    }

    return( -1 );
}