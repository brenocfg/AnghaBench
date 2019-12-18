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
typedef  int /*<<< orphan*/  d3d12_video_t ;
typedef  int /*<<< orphan*/  d3d12_texture_t ;

/* Variables and functions */
 int /*<<< orphan*/  d3d12_gfx_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3d12_release_texture (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void d3d12_gfx_unload_texture(void* data, uintptr_t handle)
{
   d3d12_texture_t* texture = (d3d12_texture_t*)handle;

   if (!texture)
      return;

   d3d12_gfx_sync((d3d12_video_t*)data);
   d3d12_release_texture(texture);
   free(texture);
}