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
 int /*<<< orphan*/  floatformat_from_doublest (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_floating_by_length (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
store_typed_floating (void *addr, const struct type *type, DOUBLEST val)
{
  gdb_assert (TYPE_CODE (type) == TYPE_CODE_FLT);

  /* FIXME: kettenis/2001-10-28: It is debatable whether we should
     zero out any remaining bytes in the target buffer when TYPE is
     longer than the actual underlying floating-point format.  Perhaps
     we should store a fixed bitpattern in those remaining bytes,
     instead of zero, or perhaps we shouldn't touch those remaining
     bytes at all.

     NOTE: cagney/2001-10-28: With the way things currently work, it
     isn't a good idea to leave the end bits undefined.  This is
     because GDB writes out the entire sizeof(<floating>) bits of the
     floating-point type even though the value might only be stored
     in, and the target processor may only refer to, the first N <
     TYPE_LENGTH (type) bits.  If the end of the buffer wasn't
     initialized, GDB would write undefined data to the target.  An
     errant program, refering to that undefined data, would then
     become non-deterministic.

     See also the function convert_typed_floating below.  */
  memset (addr, 0, TYPE_LENGTH (type));

  if (TYPE_FLOATFORMAT (type) == NULL)
    /* Not all code remembers to set the FLOATFORMAT (language
       specific code? stabs?) so handle that here as a special case.  */
    store_floating_by_length (addr, TYPE_LENGTH (type), val);
  else
    floatformat_from_doublest (TYPE_FLOATFORMAT (type), &val, addr);
}