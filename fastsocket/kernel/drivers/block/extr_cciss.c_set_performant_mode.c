#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ transMethod; int* blockFetchTable; } ;
typedef  TYPE_2__ ctlr_info_t ;
struct TYPE_6__ {size_t SGList; } ;
struct TYPE_8__ {int busaddr; TYPE_1__ Header; } ;
typedef  TYPE_3__ CommandList_struct ;

/* Variables and functions */
 scalar_t__ CFGTBL_Trans_Performant ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static void set_performant_mode(ctlr_info_t *h, CommandList_struct *c)
{
	if (likely(h->transMethod == CFGTBL_Trans_Performant))
		c->busaddr |= 1 | (h->blockFetchTable[c->Header.SGList] << 1);
}