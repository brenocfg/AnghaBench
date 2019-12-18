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
struct __gx_texobj {scalar_t__ usr_data; } ;
typedef  int /*<<< orphan*/  GXTexObj ;

/* Variables and functions */

void* GX_GetTexObjUserData(GXTexObj *obj)
{
	struct __gx_texobj *ptr = (struct __gx_texobj*)obj;
	return (void*)ptr->usr_data;
}