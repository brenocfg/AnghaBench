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
 int output_sleb128 (char*,int /*<<< orphan*/ ) ; 
 int output_uleb128 (char*,scalar_t__) ; 

int
output_leb128 (char *p, valueT value, int sign)
{
  if (sign)
    return output_sleb128 (p, (offsetT) value);
  else
    return output_uleb128 (p, value);
}