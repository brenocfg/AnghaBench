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

/* Variables and functions */
 int* ada_type_name (struct type*) ; 
 int strlen (int*) ; 

int
ada_vax_float_type_suffix (struct type *type)
{
  return ada_type_name (type)[strlen (ada_type_name (type)) - 1];
}