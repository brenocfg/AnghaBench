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
struct TYPE_3__ {int rotation; } ;
typedef  TYPE_1__ vk_t ;
struct video_ortho {int member_1; int member_3; int member_4; int member_5; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  vulkan_set_projection (TYPE_1__*,struct video_ortho*,int) ; 

__attribute__((used)) static void vulkan_set_rotation(void *data, unsigned rotation)
{
   vk_t *vk               = (vk_t*)data;
   struct video_ortho ortho = {0, 1, 0, 1, -1, 1};

   if (!vk)
      return;

   vk->rotation = 270 * rotation;
   vulkan_set_projection(vk, &ortho, true);
}