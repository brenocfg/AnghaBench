#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int hw_code; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* ati_remote2_key_table ; 

__attribute__((used)) static int ati_remote2_lookup(unsigned int hw_code)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(ati_remote2_key_table); i++)
		if (ati_remote2_key_table[i].hw_code == hw_code)
			return i;

	return -1;
}