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
struct type {int dummy; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 scalar_t__ DEPRECATED_REG_STRUCT_HAS_ADDR (int /*<<< orphan*/ ,struct type*) ; 
 scalar_t__ DEPRECATED_REG_STRUCT_HAS_ADDR_P () ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_BITSTRING ; 
 scalar_t__ TYPE_CODE_SET ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 scalar_t__ TYPE_CODE_UNION ; 
 int /*<<< orphan*/  processing_gcc_compilation ; 

int
default_stabs_argument_has_addr (struct gdbarch *gdbarch, struct type *type)
{
  if (DEPRECATED_REG_STRUCT_HAS_ADDR_P ()
      && DEPRECATED_REG_STRUCT_HAS_ADDR (processing_gcc_compilation, type))
    {
      CHECK_TYPEDEF (type);

      return (TYPE_CODE (type) == TYPE_CODE_STRUCT
	      || TYPE_CODE (type) == TYPE_CODE_UNION
	      || TYPE_CODE (type) == TYPE_CODE_SET
	      || TYPE_CODE (type) == TYPE_CODE_BITSTRING);
    }

  return 0;
}