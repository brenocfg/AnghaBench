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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ ATTR_PERMANENT_P (scalar_t__) ; 
 scalar_t__ rtx_equal_p (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
attr_equal_p (rtx x, rtx y)
{
  return (x == y || (! (ATTR_PERMANENT_P (x) && ATTR_PERMANENT_P (y))
		     && rtx_equal_p (x, y)));
}