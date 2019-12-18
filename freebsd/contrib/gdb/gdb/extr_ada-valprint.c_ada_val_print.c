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
struct ada_val_print_args {char* valaddr0; int embedded_offset; int format; int deref_ref; int recurse; int pretty; struct ui_file* stream; int /*<<< orphan*/  address; struct type* type; } ;
typedef  enum val_prettyprint { ____Placeholder_val_prettyprint } val_prettyprint ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_MASK_ALL ; 
 int /*<<< orphan*/  ada_val_print_stub ; 
 int catch_errors (int /*<<< orphan*/ ,struct ada_val_print_args*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
ada_val_print (struct type *type, char *valaddr0, int embedded_offset,
	       CORE_ADDR address, struct ui_file *stream, int format,
	       int deref_ref, int recurse, enum val_prettyprint pretty)
{
  struct ada_val_print_args args;
  args.type = type;
  args.valaddr0 = valaddr0;
  args.embedded_offset = embedded_offset;
  args.address = address;
  args.stream = stream;
  args.format = format;
  args.deref_ref = deref_ref;
  args.recurse = recurse;
  args.pretty = pretty;

  return catch_errors (ada_val_print_stub, &args, NULL, RETURN_MASK_ALL);
}