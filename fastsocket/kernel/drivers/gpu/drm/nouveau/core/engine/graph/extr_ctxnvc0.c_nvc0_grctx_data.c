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
typedef  int u32 ;
struct nvc0_grctx {int* buffer; size_t buffer_nr; int addr; TYPE_1__* data; } ;
struct TYPE_2__ {int size; int align; int access; } ;

/* Variables and functions */

void
nvc0_grctx_data(struct nvc0_grctx *info, u32 size, u32 align, u32 access)
{
	info->buffer[info->buffer_nr]  = info->addr;
	info->buffer[info->buffer_nr] +=  (align - 1);
	info->buffer[info->buffer_nr] &= ~(align - 1);
	info->addr = info->buffer[info->buffer_nr++] + size;

	info->data->size = size;
	info->data->align = align;
	info->data->access = access;
	info->data++;
}