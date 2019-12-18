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
struct TYPE_3__ {int /*<<< orphan*/  vert_buf; scalar_t__ tex; } ;
typedef  TYPE_1__ overlay_t ;
typedef  int /*<<< orphan*/  d3d9_video_t ;
typedef  int /*<<< orphan*/  LPDIRECT3DTEXTURE9 ;

/* Variables and functions */
 int /*<<< orphan*/  d3d9_texture_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_vertex_buffer_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void d3d9_free_overlay(d3d9_video_t *d3d, overlay_t *overlay)
{
   if (!d3d)
      return;

   d3d9_texture_free((LPDIRECT3DTEXTURE9)overlay->tex);
   d3d9_vertex_buffer_free(overlay->vert_buf, NULL);
}