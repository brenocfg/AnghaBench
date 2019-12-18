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
struct value {int dummy; } ;

/* Variables and functions */
 struct value* ada_value_struct_elt (struct value*,char*,char*) ; 

struct value *
ada_value_tag (struct value *val)
{
  return ada_value_struct_elt (val, "_tag", "record");
}