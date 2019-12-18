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
struct asd_ascb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  asd_unmap_scatterlist (struct asd_ascb*) ; 

__attribute__((used)) static void asd_unbuild_ata_ascb(struct asd_ascb *a)
{
	asd_unmap_scatterlist(a);
}