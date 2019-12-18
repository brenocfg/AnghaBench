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
typedef  int /*<<< orphan*/  DOUBLEST ;

/* Variables and functions */
 scalar_t__ TYPE_CODE (struct type const*) ; 
 scalar_t__ TYPE_CODE_FLT ; 
 int /*<<< orphan*/ * TYPE_FLOATFORMAT (struct type const*) ; 
 int /*<<< orphan*/  TYPE_LENGTH (struct type const*) ; 
 int /*<<< orphan*/  extract_floating_by_length (void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  floatformat_to_doublest (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 

DOUBLEST
extract_typed_floating (const void *addr, const struct type *type)
{
  DOUBLEST retval;

  gdb_assert (TYPE_CODE (type) == TYPE_CODE_FLT);

  if (TYPE_FLOATFORMAT (type) == NULL)
    /* Not all code remembers to set the FLOATFORMAT (language
       specific code? stabs?) so handle that here as a special case.  */
    return extract_floating_by_length (addr, TYPE_LENGTH (type));

  floatformat_to_doublest (TYPE_FLOATFORMAT (type), addr, &retval);
  return retval;
}