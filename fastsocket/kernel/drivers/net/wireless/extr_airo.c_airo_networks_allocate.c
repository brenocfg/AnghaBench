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
struct airo_info {scalar_t__ networks; } ;
typedef  int /*<<< orphan*/  BSSListElement ;

/* Variables and functions */
 int AIRO_MAX_NETWORK_COUNT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  airo_print_warn (char*,char*) ; 
 scalar_t__ kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int airo_networks_allocate(struct airo_info *ai)
{
	if (ai->networks)
		return 0;

	ai->networks =
	    kzalloc(AIRO_MAX_NETWORK_COUNT * sizeof(BSSListElement),
		    GFP_KERNEL);
	if (!ai->networks) {
		airo_print_warn("", "Out of memory allocating beacons");
		return -ENOMEM;
	}

	return 0;
}