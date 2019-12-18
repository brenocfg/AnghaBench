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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  dma_callback_data; int /*<<< orphan*/  (* dma_callback ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__ lcdc ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lcdc_dma_handler(u16 status, void *data)
{
	if (lcdc.dma_callback)
		lcdc.dma_callback(lcdc.dma_callback_data);
}