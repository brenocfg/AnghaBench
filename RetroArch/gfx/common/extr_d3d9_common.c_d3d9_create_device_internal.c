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
typedef  int /*<<< orphan*/  LPDIRECT3D9 ;
typedef  int /*<<< orphan*/  IDirect3DDevice9 ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  D3DPRESENT_PARAMETERS ;

/* Variables and functions */
 int /*<<< orphan*/  D3DDEVTYPE_HAL ; 
 int /*<<< orphan*/  IDirect3D9_CreateDevice (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool d3d9_create_device_internal(
      void *data,
      D3DPRESENT_PARAMETERS *d3dpp,
      void *_d3d,
      HWND focus_window,
      unsigned cur_mon_id,
      DWORD behavior_flags)
{
   LPDIRECT3D9       d3d = (LPDIRECT3D9)_d3d;
   LPDIRECT3DDEVICE9 dev = (LPDIRECT3DDEVICE9)data;
   if (dev &&
         SUCCEEDED(IDirect3D9_CreateDevice(d3d,
               cur_mon_id,
               D3DDEVTYPE_HAL,
               focus_window,
               behavior_flags,
               d3dpp,
               (IDirect3DDevice9**)dev)))
      return true;

   return false;
}