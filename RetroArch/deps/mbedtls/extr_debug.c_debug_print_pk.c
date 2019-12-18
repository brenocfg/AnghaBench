#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  mbedtls_ssl_context ;
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ mbedtls_pk_debug_item ;
typedef  int /*<<< orphan*/  mbedtls_pk_context ;
typedef  int /*<<< orphan*/  items ;

/* Variables and functions */
 scalar_t__ MBEDTLS_PK_DEBUG_ECP ; 
 int MBEDTLS_PK_DEBUG_MAX_ITEMS ; 
 scalar_t__ MBEDTLS_PK_DEBUG_MPI ; 
 scalar_t__ MBEDTLS_PK_DEBUG_NONE ; 
 int /*<<< orphan*/  debug_send_line (int /*<<< orphan*/  const*,int,char const*,int,char*) ; 
 int /*<<< orphan*/  mbedtls_debug_print_ecp (int /*<<< orphan*/  const*,int,char const*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_debug_print_mpi (int /*<<< orphan*/  const*,int,char const*,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ mbedtls_pk_debug (int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_snprintf (char*,int,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void debug_print_pk( const mbedtls_ssl_context *ssl, int level,
                            const char *file, int line,
                            const char *text, const mbedtls_pk_context *pk )
{
    size_t i;
    mbedtls_pk_debug_item items[MBEDTLS_PK_DEBUG_MAX_ITEMS];
    char name[16];

    memset( items, 0, sizeof( items ) );

    if( mbedtls_pk_debug( pk, items ) != 0 )
    {
        debug_send_line( ssl, level, file, line,
                          "invalid PK context\n" );
        return;
    }

    for( i = 0; i < MBEDTLS_PK_DEBUG_MAX_ITEMS; i++ )
    {
        if( items[i].type == MBEDTLS_PK_DEBUG_NONE )
            return;

        mbedtls_snprintf( name, sizeof( name ), "%s%s", text, items[i].name );
        name[sizeof( name ) - 1] = '\0';

        if( items[i].type == MBEDTLS_PK_DEBUG_MPI )
            mbedtls_debug_print_mpi( ssl, level, file, line, name, items[i].value );
        else
#if defined(MBEDTLS_ECP_C)
        if( items[i].type == MBEDTLS_PK_DEBUG_ECP )
            mbedtls_debug_print_ecp( ssl, level, file, line, name, items[i].value );
        else
#endif
            debug_send_line( ssl, level, file, line,
                              "should not happen\n" );
    }
}