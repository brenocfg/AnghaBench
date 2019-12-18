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
struct ui_file {int dummy; } ;
struct type {int dummy; } ;
typedef  enum val_prettyprint { ____Placeholder_val_prettyprint } val_prettyprint ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */

int
m2_val_print (struct type *type, char *valaddr, int embedded_offset,
	      CORE_ADDR address, struct ui_file *stream, int format,
	      int deref_ref, int recurse, enum val_prettyprint pretty)
{
  extern int c_val_print (struct type *, char *, int, CORE_ADDR,
			  struct ui_file *, int, int, int,
			  enum val_prettyprint);
  return (c_val_print (type, valaddr, 0, address, stream, format, deref_ref,
		       recurse, pretty));
}