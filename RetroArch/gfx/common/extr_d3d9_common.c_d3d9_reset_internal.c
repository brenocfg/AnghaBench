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
typedef  scalar_t__ LPDIRECT3DDEVICE9 ;
typedef  int /*<<< orphan*/  D3DPRESENT_PARAMETERS ;

/* Variables and functions */
 scalar_t__ D3D_OK ; 
 scalar_t__ IDirect3DDevice9_Reset (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool d3d9_reset_internal(void *data,
      D3DPRESENT_PARAMETERS *d3dpp
      )
{
   LPDIRECT3DDEVICE9 dev = (LPDIRECT3DDEVICE9)data;
   if (dev &&
         IDirect3DDevice9_Reset(dev, d3dpp) == D3D_OK)
      return true;

   return false;
}