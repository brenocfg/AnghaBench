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
 int /*<<< orphan*/  floatformat_from_doublest (struct floatformat const*,int /*<<< orphan*/ *,void*) ; 
 struct floatformat* floatformat_from_length (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  warning (char*,int) ; 

__attribute__((used)) static void
store_floating_by_length (void *addr, int len, DOUBLEST val)
{
  const struct floatformat *fmt = floatformat_from_length (len);

  if (fmt == NULL)
    {
      warning ("Can't store a floating-point number of %d bytes.", len);
      memset (addr, 0, len);
      return;
    }

  floatformat_from_doublest (fmt, &val, addr);
}