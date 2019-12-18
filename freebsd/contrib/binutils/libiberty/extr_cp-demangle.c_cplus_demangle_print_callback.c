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
struct demangle_component {int dummy; } ;
struct d_print_info {int dummy; } ;
typedef  int /*<<< orphan*/  demangle_callbackref ;

/* Variables and functions */
 int /*<<< orphan*/  d_print_comp (struct d_print_info*,struct demangle_component const*) ; 
 int /*<<< orphan*/  d_print_flush (struct d_print_info*) ; 
 int /*<<< orphan*/  d_print_init (struct d_print_info*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  d_print_saw_error (struct d_print_info*) ; 

int
cplus_demangle_print_callback (int options,
                               const struct demangle_component *dc,
                               demangle_callbackref callback, void *opaque)
{
  struct d_print_info dpi;

  d_print_init (&dpi, options, callback, opaque);

  d_print_comp (&dpi, dc);

  d_print_flush (&dpi);

  return ! d_print_saw_error (&dpi);
}