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
 int /*<<< orphan*/  TYPE_LENGTH (struct type*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_equivalent_f77_float_type (struct type *type, struct ui_file *stream)
{
  /* Override type name "float" and make it the
     appropriate real. XLC stupidly outputs -12 as a type
     for real when it really should be outputting -18 */

  fprintf_filtered (stream, "real*%d", TYPE_LENGTH (type));
}