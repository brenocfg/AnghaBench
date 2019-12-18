#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * dev_id; int /*<<< orphan*/ * handler; } ;
struct TYPE_3__ {int intr_cimr; } ;

/* Variables and functions */
 TYPE_2__* cpm_vecs ; 
 TYPE_1__* pquicc ; 

void
cpm_free_handler(int vec)
{
	cpm_vecs[vec].handler = NULL;
	cpm_vecs[vec].dev_id = NULL;
	/* ((immap_t *)IMAP_ADDR)->im_cpic.cpic_cimr &= ~(1 << vec); */
	pquicc->intr_cimr &= ~(1 << vec);
}