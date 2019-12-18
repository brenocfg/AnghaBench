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
typedef  double DOUBLEST ;

/* Variables and functions */
 double ada_delta (struct type*) ; 
 double ada_fixed_to_float (struct type*,double) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 

__attribute__((used)) static void
print_fixed_point_type (struct type *type, struct ui_file *stream)
{
  DOUBLEST delta = ada_delta (type);
  DOUBLEST small = ada_fixed_to_float (type, 1.0);

  if (delta < 0.0)
    fprintf_filtered (stream, "delta ??");
  else
    {
      fprintf_filtered (stream, "delta %g", (double) delta);
      if (delta != small)
	fprintf_filtered (stream, " <'small = %g>", (double) small);
    }
}