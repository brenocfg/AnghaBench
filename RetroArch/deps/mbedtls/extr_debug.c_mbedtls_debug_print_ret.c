#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  str ;
struct TYPE_6__ {TYPE_1__* conf; } ;
typedef  TYPE_2__ mbedtls_ssl_context ;
struct TYPE_5__ {int /*<<< orphan*/ * f_dbg; } ;

/* Variables and functions */
 int DEBUG_BUF_SIZE ; 
 int MBEDTLS_ERR_SSL_WANT_READ ; 
 int /*<<< orphan*/  debug_send_line (TYPE_2__ const*,int,char const*,int,char*) ; 
 int debug_threshold ; 
 int /*<<< orphan*/  mbedtls_snprintf (char*,int,char*,char const*,int,int) ; 

void mbedtls_debug_print_ret( const mbedtls_ssl_context *ssl, int level,
                      const char *file, int line,
                      const char *text, int ret )
{
    char str[DEBUG_BUF_SIZE];

    if( ssl->conf == NULL || ssl->conf->f_dbg == NULL || level > debug_threshold )
        return;

    /*
     * With non-blocking I/O and examples that just retry immediately,
     * the logs would be quickly flooded with WANT_READ, so ignore that.
     * Don't ignore WANT_WRITE however, since is is usually rare.
     */
    if( ret == MBEDTLS_ERR_SSL_WANT_READ )
        return;

    mbedtls_snprintf( str, sizeof( str ), "%s() returned %d (-0x%04x)\n",
              text, ret, -ret );

    debug_send_line( ssl, level, file, line, str );
}