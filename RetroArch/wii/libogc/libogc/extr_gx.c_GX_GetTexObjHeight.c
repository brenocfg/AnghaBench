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
typedef  scalar_t__ u16 ;
struct __gx_texobj {int tex_size; } ;
typedef  int /*<<< orphan*/  GXTexObj ;

/* Variables and functions */
 scalar_t__ _SHIFTR (int,int,int) ; 

u16 GX_GetTexObjHeight(GXTexObj* obj)
{
	return _SHIFTR(((struct __gx_texobj*)obj)->tex_size & 0xffc00, 10, 10) + 1;
}