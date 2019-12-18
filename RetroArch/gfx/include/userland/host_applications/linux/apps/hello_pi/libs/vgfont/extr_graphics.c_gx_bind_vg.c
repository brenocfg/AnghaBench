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
typedef  int /*<<< orphan*/  VCOS_STATUS_T ;
typedef  int /*<<< orphan*/  GX_CLIENT_STATE_T ;
typedef  int /*<<< orphan*/  GRAPHICS_RESOURCE_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_SUCCESS ; 
 int /*<<< orphan*/  gx_priv_save (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 scalar_t__ vgGetError () ; 

VCOS_STATUS_T gx_bind_vg( GX_CLIENT_STATE_T *save, GRAPHICS_RESOURCE_HANDLE res )
{
   gx_priv_save(save, res);
   vcos_assert(vgGetError()==0);
   return VCOS_SUCCESS;
}