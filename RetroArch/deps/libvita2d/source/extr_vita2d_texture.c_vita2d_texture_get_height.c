#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  gxm_tex; } ;
typedef  TYPE_1__ vita2d_texture ;

/* Variables and functions */
 unsigned int sceGxmTextureGetHeight (int /*<<< orphan*/ *) ; 

unsigned int vita2d_texture_get_height(const vita2d_texture *texture)
{
	return sceGxmTextureGetHeight(&texture->gxm_tex);
}