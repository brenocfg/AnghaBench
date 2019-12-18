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
struct nfs_delegation {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfs_delegation*) ; 

__attribute__((used)) static void nfs_do_free_delegation(struct nfs_delegation *delegation)
{
	kfree(delegation);
}