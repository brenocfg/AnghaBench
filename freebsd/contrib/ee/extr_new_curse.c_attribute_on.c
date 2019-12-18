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

/* Variables and functions */
 int /*<<< orphan*/  String_Out (scalar_t__,int*,int) ; 
 scalar_t__* String_table ; 
 int* attributes_set ; 
 size_t sa__ ; 
 size_t so__ ; 

void 
attribute_on()
{
	if (String_table[sa__])
	{
		attributes_set[0] = 1;
		String_Out(String_table[sa__], attributes_set, 1);
	}
	else if (String_table[so__])
		String_Out(String_table[so__], NULL, 0);
}