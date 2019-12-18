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
struct vita2d_texture {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vita2d_free_texture (struct vita2d_texture*) ; 
 int /*<<< orphan*/  vita2d_wait_rendering_done () ; 

__attribute__((used)) static void vita_unload_texture(void *data, uintptr_t handle)
{
   struct vita2d_texture *texture = (struct vita2d_texture*)handle;
   if (!texture)
      return;

   /* TODO: We really want to defer this deletion instead,
    * but this will do for now. */
   vita2d_wait_rendering_done();
   vita2d_free_texture(texture);

   //free(texture);
}