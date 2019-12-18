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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_fprintf (int /*<<< orphan*/ *,char*,char const*,int,char const*) ; 

__attribute__((used)) static void ssl_debug(void *ctx, int level,
                      const char *file, int line,
                      const char *str)
{
   ((void) level);

   mbedtls_fprintf((FILE*)ctx, "%s:%04d: %s", file, line, str);
   fflush((FILE*)ctx);
}