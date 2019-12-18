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
struct TYPE_3__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  staging; int /*<<< orphan*/  view; } ;
typedef  TYPE_1__ d3d10_texture_t ;

/* Variables and functions */
 int /*<<< orphan*/  Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void d3d10_gfx_unload_texture(void* data, uintptr_t handle)
{
   d3d10_texture_t* texture = (d3d10_texture_t*)handle;

   if (!texture)
      return;

   Release(texture->view);
   Release(texture->staging);
   Release(texture->handle);
   free(texture);
}