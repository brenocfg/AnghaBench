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
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_refcount; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_layout_hdr (struct pnfs_layout_hdr*) ; 

__attribute__((used)) static void
pnfs_put_layout_hdr_locked(struct pnfs_layout_hdr *lo)
{
	if (atomic_dec_and_test(&lo->plh_refcount))
		destroy_layout_hdr(lo);
}