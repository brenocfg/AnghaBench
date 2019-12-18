#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  flicker_filter_index; } ;
struct TYPE_6__ {int /*<<< orphan*/  softfilter_enable; TYPE_1__ screen; } ;
struct TYPE_7__ {TYPE_2__ console; } ;
typedef  TYPE_3__ global_t ;

/* Variables and functions */
 int /*<<< orphan*/  D3DDevice_SetFlickerFilter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D3DDevice_SetSoftDisplayFilter (int /*<<< orphan*/ ) ; 
 TYPE_3__* global_get_ptr () ; 

void d3d8_frame_postprocess(void *data)
{
#if defined(_XBOX)
   global_t        *global = global_get_ptr();
   D3DDevice_SetFlickerFilter(global->console.screen.flicker_filter_index);
   D3DDevice_SetSoftDisplayFilter(global->console.softfilter_enable);
#endif
}