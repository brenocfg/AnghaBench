#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ufs_sb_private_info {int dummy; } ;
struct TYPE_2__ {unsigned int count; int /*<<< orphan*/ ** bh; } ;

/* Variables and functions */
 TYPE_1__* USPI_UBH (struct ufs_sb_private_info*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 

void ubh_brelse_uspi (struct ufs_sb_private_info * uspi)
{
	unsigned i;
	if (!USPI_UBH(uspi))
		return;
	for ( i = 0; i < USPI_UBH(uspi)->count; i++ ) {
		brelse (USPI_UBH(uspi)->bh[i]);
		USPI_UBH(uspi)->bh[i] = NULL;
	}
}