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
typedef  size_t ip_set_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  __ip_set_put (size_t) ; 
 int /*<<< orphan*/ ** ip_set_list ; 

void
ip_set_put_byindex(ip_set_id_t index)
{
	if (ip_set_list[index] != NULL)
		__ip_set_put(index);
}