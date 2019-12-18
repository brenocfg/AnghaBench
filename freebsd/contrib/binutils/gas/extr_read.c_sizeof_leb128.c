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
typedef  scalar_t__ valueT ;
typedef  int /*<<< orphan*/  offsetT ;

/* Variables and functions */
 int sizeof_sleb128 (int /*<<< orphan*/ ) ; 
 int sizeof_uleb128 (scalar_t__) ; 

int
sizeof_leb128 (valueT value, int sign)
{
  if (sign)
    return sizeof_sleb128 ((offsetT) value);
  else
    return sizeof_uleb128 (value);
}