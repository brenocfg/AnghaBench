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
struct ghes {int flags; int /*<<< orphan*/  buffer_paddr; TYPE_1__* estatus; } ;
struct TYPE_2__ {scalar_t__ block_status; } ;

/* Variables and functions */
 int GHES_TO_CLEAR ; 
 int /*<<< orphan*/  ghes_copy_tofrom_phys (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ghes_clear_estatus(struct ghes *ghes)
{
	ghes->estatus->block_status = 0;
	if (!(ghes->flags & GHES_TO_CLEAR))
		return;
	ghes_copy_tofrom_phys(ghes->estatus, ghes->buffer_paddr,
			      sizeof(ghes->estatus->block_status), 0);
	ghes->flags &= ~GHES_TO_CLEAR;
}