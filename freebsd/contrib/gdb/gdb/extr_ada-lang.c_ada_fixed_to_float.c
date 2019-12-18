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
typedef  scalar_t__ LONGEST ;
typedef  int DOUBLEST ;

/* Variables and functions */
 int scaling_factor (struct type*) ; 

DOUBLEST
ada_fixed_to_float (struct type *type, LONGEST x)
{
  return (DOUBLEST) x *scaling_factor (type);
}