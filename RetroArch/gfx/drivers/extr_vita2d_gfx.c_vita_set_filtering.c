#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tex_filter; int /*<<< orphan*/  texture; } ;
typedef  TYPE_1__ vita_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCE_GXM_TEXTURE_FILTER_LINEAR ; 
 int /*<<< orphan*/  SCE_GXM_TEXTURE_FILTER_POINT ; 
 int /*<<< orphan*/  vita2d_texture_set_filters (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vita_set_filtering(void *data, unsigned index, bool smooth)
{
   vita_video_t *vita = (vita_video_t *)data;

   if (vita)
   {
      vita->tex_filter = smooth ?
         SCE_GXM_TEXTURE_FILTER_LINEAR : SCE_GXM_TEXTURE_FILTER_POINT;
      vita2d_texture_set_filters(vita->texture,vita->tex_filter,
            vita->tex_filter);
   }
}