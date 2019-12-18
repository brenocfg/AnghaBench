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
 int /*<<< orphan*/  nfsd_drc_lock ; 
 int nfsd_drc_mem_used ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfsd4_put_drc_mem(int slotsize, int num)
{
	spin_lock(&nfsd_drc_lock);
	nfsd_drc_mem_used -= slotsize * num;
	spin_unlock(&nfsd_drc_lock);
}