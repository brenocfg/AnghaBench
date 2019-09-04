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
 int __hcreate_r (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htab ; 

int hcreate(size_t nel)
{
	return __hcreate_r(nel, &htab);
}