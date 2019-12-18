#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  image; } ;
struct TYPE_5__ {TYPE_1__ surface; } ;
typedef  TYPE_2__ GX2Texture ;

/* Variables and functions */
 int /*<<< orphan*/  MEM2_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void wiiu_gfx_unload_texture(void *data, uintptr_t handle)
{
   GX2Texture *texture = (GX2Texture *)handle;

   if (!texture)
      return;

   MEM2_free(texture->surface.image);
   free(texture);
}