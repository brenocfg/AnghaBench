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
struct floatformat {int dummy; } ;
typedef  int /*<<< orphan*/  DOUBLEST ;

/* Variables and functions */
 scalar_t__ TYPE_CODE (struct type const*) ; 
 scalar_t__ TYPE_CODE_FLT ; 
 int /*<<< orphan*/  TYPE_LENGTH (struct type const*) ; 
 int /*<<< orphan*/  floatformat_from_doublest (struct floatformat const*,int /*<<< orphan*/ *,void*) ; 
 struct floatformat* floatformat_from_type (struct type const*) ; 
 int /*<<< orphan*/  floatformat_to_doublest (struct floatformat const*,void const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*) ; 

void
convert_typed_floating (const void *from, const struct type *from_type,
                        void *to, const struct type *to_type)
{
  const struct floatformat *from_fmt = floatformat_from_type (from_type);
  const struct floatformat *to_fmt = floatformat_from_type (to_type);

  gdb_assert (TYPE_CODE (from_type) == TYPE_CODE_FLT);
  gdb_assert (TYPE_CODE (to_type) == TYPE_CODE_FLT);

  if (from_fmt == NULL || to_fmt == NULL)
    {
      /* If we don't know the floating-point format of FROM_TYPE or
         TO_TYPE, there's not much we can do.  We might make the
         assumption that if the length of FROM_TYPE and TO_TYPE match,
         their floating-point format would match too, but that
         assumption might be wrong on targets that support
         floating-point types that only differ in endianness for
         example.  So we warn instead, and zero out the target buffer.  */
      warning ("Can't convert floating-point number to desired type.");
      memset (to, 0, TYPE_LENGTH (to_type));
    }
  else if (from_fmt == to_fmt)
    {
      /* We're in business.  The floating-point format of FROM_TYPE
         and TO_TYPE match.  However, even though the floating-point
         format matches, the length of the type might still be
         different.  Make sure we don't overrun any buffers.  See
         comment in store_typed_floating for a discussion about
         zeroing out remaining bytes in the target buffer.  */
      memset (to, 0, TYPE_LENGTH (to_type));
      memcpy (to, from, min (TYPE_LENGTH (from_type), TYPE_LENGTH (to_type)));
    }
  else
    {
      /* The floating-point types don't match.  The best we can do
         (aport from simulating the target FPU) is converting to the
         widest floating-point type supported by the host, and then
         again to the desired type.  */
      DOUBLEST d;

      floatformat_to_doublest (from_fmt, from, &d);
      floatformat_from_doublest (to_fmt, &d, to);
    }
}