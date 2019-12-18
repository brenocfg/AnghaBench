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
struct ada_val_print_args {int /*<<< orphan*/  pretty; int /*<<< orphan*/  recurse; int /*<<< orphan*/  deref_ref; int /*<<< orphan*/  format; int /*<<< orphan*/  stream; int /*<<< orphan*/  address; int /*<<< orphan*/  embedded_offset; int /*<<< orphan*/  valaddr0; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ada_val_print_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ada_val_print_stub (void * args0)
{
  struct ada_val_print_args *argsp = (struct ada_val_print_args *) args0;
  return ada_val_print_1 (argsp->type, argsp->valaddr0,
			  argsp->embedded_offset, argsp->address,
			  argsp->stream, argsp->format, argsp->deref_ref,
			  argsp->recurse, argsp->pretty);
}