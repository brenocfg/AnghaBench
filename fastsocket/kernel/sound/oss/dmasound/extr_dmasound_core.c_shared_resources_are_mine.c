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
typedef  int fmode_t ;

/* Variables and functions */
 int shared_resource_owner ; 

__attribute__((used)) static int shared_resources_are_mine(fmode_t md)
{
	if (shared_resource_owner)
		return (shared_resource_owner & md) != 0;
	else {
		shared_resource_owner = md ;
		return 1 ;
	}
}