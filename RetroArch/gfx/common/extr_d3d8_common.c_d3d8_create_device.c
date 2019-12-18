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
typedef  int /*<<< orphan*/  LPDIRECT3D8 ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  D3DPRESENT_PARAMETERS ;

/* Variables and functions */
 int /*<<< orphan*/  D3DCREATE_HARDWARE_VERTEXPROCESSING ; 
 int /*<<< orphan*/  D3DCREATE_SOFTWARE_VERTEXPROCESSING ; 
 int /*<<< orphan*/  d3d8_create_device_internal (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

bool d3d8_create_device(void *dev,
      void *d3dpp,
      LPDIRECT3D8 d3d,
      HWND focus_window,
      unsigned cur_mon_id)
{
   if (!d3d8_create_device_internal(dev,
            (D3DPRESENT_PARAMETERS*)d3dpp,
            d3d,
            focus_window,
            cur_mon_id,
            D3DCREATE_HARDWARE_VERTEXPROCESSING))
      if (!d3d8_create_device_internal(
               dev,
               (D3DPRESENT_PARAMETERS*)d3dpp, d3d, focus_window,
               cur_mon_id,
               D3DCREATE_SOFTWARE_VERTEXPROCESSING))
         return false;
   return true;
}