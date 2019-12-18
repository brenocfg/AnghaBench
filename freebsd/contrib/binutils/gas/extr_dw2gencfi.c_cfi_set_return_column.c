#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* frch_cfi_data; } ;
struct TYPE_5__ {TYPE_1__* cur_fde_data; } ;
struct TYPE_4__ {unsigned int return_column; } ;

/* Variables and functions */
 TYPE_3__* frchain_now ; 

void
cfi_set_return_column (unsigned regno)
{
  frchain_now->frch_cfi_data->cur_fde_data->return_column = regno;
}