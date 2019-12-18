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
typedef  scalar_t__ LPDIRECT3DDEVICE8 ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  IDirect3DDevice8_TestCooperativeLevel (scalar_t__) ; 

__attribute__((used)) static HRESULT d3d8_test_cooperative_level(LPDIRECT3DDEVICE8 dev)
{
#ifndef _XBOX
   if (dev)
      return IDirect3DDevice8_TestCooperativeLevel(dev);
#endif
   return E_FAIL;
}