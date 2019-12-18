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
struct mgsl_struct {int /*<<< orphan*/ * intermediate_rxbuffer; int /*<<< orphan*/  max_frame_size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mgsl_alloc_intermediate_rxbuffer_memory(struct mgsl_struct *info)
{
	info->intermediate_rxbuffer = kmalloc(info->max_frame_size, GFP_KERNEL | GFP_DMA);
	if ( info->intermediate_rxbuffer == NULL )
		return -ENOMEM;

	return 0;

}