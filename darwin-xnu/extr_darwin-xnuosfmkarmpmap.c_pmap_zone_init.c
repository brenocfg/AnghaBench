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
typedef  int vm_size_t ;
struct pmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  pmap_zone ; 
 int /*<<< orphan*/  zinit (int,int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
pmap_zone_init(
	void)
{
	/*
	 *	Create the zone of physical maps
	 *	and the physical-to-virtual entries.
	 */
	pmap_zone = zinit((vm_size_t) sizeof(struct pmap), (vm_size_t) sizeof(struct pmap)*256,
	                  PAGE_SIZE, "pmap");
}