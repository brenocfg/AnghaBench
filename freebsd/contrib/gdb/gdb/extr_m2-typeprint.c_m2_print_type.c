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

/* Variables and functions */

void
m2_print_type (struct type *type, char *varstring, struct ui_file *stream,
	       int show, int level)
{
  extern void c_print_type (struct type *, char *, struct ui_file *, int,
			    int);

  c_print_type (type, varstring, stream, show, level);	/* FIXME */
}