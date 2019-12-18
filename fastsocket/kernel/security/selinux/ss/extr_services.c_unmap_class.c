#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct TYPE_2__ {size_t value; } ;

/* Variables and functions */
 TYPE_1__* current_mapping ; 
 size_t current_mapping_size ; 

__attribute__((used)) static u16 unmap_class(u16 tclass)
{
	if (tclass < current_mapping_size)
		return current_mapping[tclass].value;

	return tclass;
}