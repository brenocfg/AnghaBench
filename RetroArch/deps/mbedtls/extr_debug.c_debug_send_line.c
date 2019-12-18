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
struct TYPE_5__ {TYPE_1__* conf; } ;
typedef  TYPE_2__ mbedtls_ssl_context ;
typedef  int /*<<< orphan*/  idstr ;
struct TYPE_4__ {int /*<<< orphan*/  p_dbg; int /*<<< orphan*/  (* f_dbg ) (int /*<<< orphan*/ ,int,char const*,int,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_BUF_SIZE ; 
 int /*<<< orphan*/  mbedtls_snprintf (char*,int,char*,void*,char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,char const*,int,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,char const*,int,char const*) ; 

__attribute__((used)) static void debug_send_line( const mbedtls_ssl_context *ssl, int level,
                                    const char *file, int line,
                                    const char *str )
{
    /*
     * If in a threaded environment, we need a thread identifier.
     * Since there is no portable way to get one, use the address of the ssl
     * context instead, as it shouldn't be shared between threads.
     */
#if defined(MBEDTLS_THREADING_C)
    char idstr[20 + DEBUG_BUF_SIZE]; /* 0x + 16 nibbles + ': ' */
    mbedtls_snprintf( idstr, sizeof( idstr ), "%p: %s", (void*)ssl, str );
    ssl->conf->f_dbg( ssl->conf->p_dbg, level, file, line, idstr );
#else
    ssl->conf->f_dbg( ssl->conf->p_dbg, level, file, line, str );
#endif
}