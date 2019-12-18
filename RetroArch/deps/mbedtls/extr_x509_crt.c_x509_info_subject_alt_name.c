#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t len; int /*<<< orphan*/ * p; } ;
struct TYPE_5__ {struct TYPE_5__* next; TYPE_1__ buf; } ;
typedef  TYPE_2__ mbedtls_x509_sequence ;

/* Variables and functions */
 int MBEDTLS_ERR_X509_BUFFER_TOO_SMALL ; 

__attribute__((used)) static int x509_info_subject_alt_name( char **buf, size_t *size,
                                       const mbedtls_x509_sequence *subject_alt_name )
{
    size_t i;
    size_t n = *size;
    char *p = *buf;
    const mbedtls_x509_sequence *cur = subject_alt_name;
    const char *sep = "";
    size_t sep_len = 0;

    while( cur != NULL )
    {
        if( cur->buf.len + sep_len >= n )
        {
            *p = '\0';
            return( MBEDTLS_ERR_X509_BUFFER_TOO_SMALL );
        }

        n -= cur->buf.len + sep_len;
        for( i = 0; i < sep_len; i++ )
            *p++ = sep[i];
        for( i = 0; i < cur->buf.len; i++ )
            *p++ = cur->buf.p[i];

        sep = ", ";
        sep_len = 2;

        cur = cur->next;
    }

    *p = '\0';

    *size = n;
    *buf = p;

    return( 0 );
}