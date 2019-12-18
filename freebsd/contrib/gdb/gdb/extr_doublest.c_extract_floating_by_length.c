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
struct floatformat {int dummy; } ;
typedef  int /*<<< orphan*/  DOUBLEST ;

/* Variables and functions */
 int /*<<< orphan*/  NAN ; 
 struct floatformat* floatformat_from_length (int) ; 
 int /*<<< orphan*/  floatformat_to_doublest (struct floatformat const*,void const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warning (char*,int) ; 

__attribute__((used)) static DOUBLEST
extract_floating_by_length (const void *addr, int len)
{
  const struct floatformat *fmt = floatformat_from_length (len);
  DOUBLEST val;

  if (fmt == NULL)
    {
      warning ("Can't extract a floating-point number of %d bytes.", len);
      return NAN;
    }

  floatformat_to_doublest (fmt, addr, &val);
  return val;
}