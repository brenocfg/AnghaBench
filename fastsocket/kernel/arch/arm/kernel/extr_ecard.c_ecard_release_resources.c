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
struct expansion_card {int dummy; } ;

/* Variables and functions */
 int ECARD_NUM_RESOURCES ; 
 scalar_t__ ecard_resource_end (struct expansion_card*,int) ; 
 int /*<<< orphan*/  ecard_resource_len (struct expansion_card*,int) ; 
 int /*<<< orphan*/  ecard_resource_start (struct expansion_card*,int) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ecard_release_resources(struct expansion_card *ec)
{
	int i;

	for (i = 0; i < ECARD_NUM_RESOURCES; i++)
		if (ecard_resource_end(ec, i))
			release_mem_region(ecard_resource_start(ec, i),
					   ecard_resource_len(ec, i));
}