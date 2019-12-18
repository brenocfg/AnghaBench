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
typedef  int /*<<< orphan*/  symbolS ;
struct fde_entry {int /*<<< orphan*/ * start_address; } ;
struct TYPE_4__ {TYPE_1__* frch_cfi_data; } ;
struct TYPE_3__ {int /*<<< orphan*/ * last_address; } ;

/* Variables and functions */
 struct fde_entry* alloc_fde_entry () ; 
 TYPE_2__* frchain_now ; 

void 
cfi_new_fde (symbolS *label)
{
  struct fde_entry *fde = alloc_fde_entry ();
  fde->start_address = label;
  frchain_now->frch_cfi_data->last_address = label;
}