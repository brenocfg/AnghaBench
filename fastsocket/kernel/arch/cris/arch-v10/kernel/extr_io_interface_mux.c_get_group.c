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
struct if_group {unsigned char const group; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct if_group*) ; 
 struct if_group* if_groups ; 

__attribute__((used)) static struct if_group *get_group(const unsigned char groups)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(if_groups); i++) {
		if (groups & if_groups[i].group) {
			return &if_groups[i];
		}
	}
	return NULL;
}