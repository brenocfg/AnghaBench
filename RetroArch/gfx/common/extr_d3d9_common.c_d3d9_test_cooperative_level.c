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
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  IDirect3DDevice9_TestCooperativeLevel (scalar_t__) ; 

__attribute__((used)) static HRESULT d3d9_test_cooperative_level(void *data)
{
#ifndef _XBOX
   LPDIRECT3DDEVICE9 dev = (LPDIRECT3DDEVICE9)data;
   if (dev)
      return IDirect3DDevice9_TestCooperativeLevel(dev);
#endif
   return E_FAIL;
}