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
struct d_print_info {int options; char last_char; scalar_t__ demangle_failure; void* opaque; int /*<<< orphan*/  callback; int /*<<< orphan*/ * modifiers; int /*<<< orphan*/ * templates; scalar_t__ len; } ;
typedef  int /*<<< orphan*/  demangle_callbackref ;

/* Variables and functions */

__attribute__((used)) static void
d_print_init (struct d_print_info *dpi, int options,
              demangle_callbackref callback, void *opaque)
{
  dpi->options = options;
  dpi->len = 0;
  dpi->last_char = '\0';
  dpi->templates = NULL;
  dpi->modifiers = NULL;

  dpi->callback = callback;
  dpi->opaque = opaque;

  dpi->demangle_failure = 0;
}