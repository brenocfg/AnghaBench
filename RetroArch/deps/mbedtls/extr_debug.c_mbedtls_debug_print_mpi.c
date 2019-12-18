#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  str ;
struct TYPE_8__ {TYPE_1__* conf; } ;
typedef  TYPE_2__ mbedtls_ssl_context ;
typedef  int /*<<< orphan*/  mbedtls_mpi_uint ;
struct TYPE_9__ {int n; int* p; } ;
typedef  TYPE_3__ mbedtls_mpi ;
struct TYPE_7__ {int /*<<< orphan*/ * f_dbg; } ;

/* Variables and functions */
 int DEBUG_BUF_SIZE ; 
 int /*<<< orphan*/  debug_send_line (TYPE_2__ const*,int,char const*,int,char*) ; 
 int debug_threshold ; 
 scalar_t__ mbedtls_snprintf (char*,int,char*,...) ; 

void mbedtls_debug_print_mpi( const mbedtls_ssl_context *ssl, int level,
                      const char *file, int line,
                      const char *text, const mbedtls_mpi *X )
{
    char str[DEBUG_BUF_SIZE];
    int j, k, zeros = 1;
    size_t i, n, idx = 0;

    if( ssl->conf == NULL || ssl->conf->f_dbg == NULL || X == NULL || level > debug_threshold )
        return;

    for( n = X->n - 1; n > 0; n-- )
        if( X->p[n] != 0 )
            break;

    for( j = ( sizeof(mbedtls_mpi_uint) << 3 ) - 1; j >= 0; j-- )
        if( ( ( X->p[n] >> j ) & 1 ) != 0 )
            break;

    mbedtls_snprintf( str + idx, sizeof( str ) - idx, "value of '%s' (%d bits) is:\n",
              text, (int) ( ( n * ( sizeof(mbedtls_mpi_uint) << 3 ) ) + j + 1 ) );

    debug_send_line( ssl, level, file, line, str );

    idx = 0;
    for( i = n + 1, j = 0; i > 0; i-- )
    {
        if( zeros && X->p[i - 1] == 0 )
            continue;

        for( k = sizeof( mbedtls_mpi_uint ) - 1; k >= 0; k-- )
        {
            if( zeros && ( ( X->p[i - 1] >> ( k << 3 ) ) & 0xFF ) == 0 )
                continue;
            else
                zeros = 0;

            if( j % 16 == 0 )
            {
                if( j > 0 )
                {
                    mbedtls_snprintf( str + idx, sizeof( str ) - idx, "\n" );
                    debug_send_line( ssl, level, file, line, str );
                    idx = 0;
                }
            }

            idx += mbedtls_snprintf( str + idx, sizeof( str ) - idx, " %02x", (unsigned int)
                             ( X->p[i - 1] >> ( k << 3 ) ) & 0xFF );

            j++;
        }

    }

    if( zeros == 1 )
        idx += mbedtls_snprintf( str + idx, sizeof( str ) - idx, " 00" );

    mbedtls_snprintf( str + idx, sizeof( str ) - idx, "\n" );
    debug_send_line( ssl, level, file, line, str );
}