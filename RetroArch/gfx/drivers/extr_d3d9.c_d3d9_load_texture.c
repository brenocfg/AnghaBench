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
struct d3d9_texture_info {int type; void* data; void* userdata; } ;
typedef  enum texture_filter_type { ____Placeholder_texture_filter_type } texture_filter_type ;

/* Variables and functions */
 int /*<<< orphan*/  d3d9_video_texture_load_d3d (struct d3d9_texture_info*,uintptr_t*) ; 
 int /*<<< orphan*/  d3d9_video_texture_load_wrap_d3d ; 
 uintptr_t video_thread_texture_load (struct d3d9_texture_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uintptr_t d3d9_load_texture(void *video_data, void *data,
      bool threaded, enum texture_filter_type filter_type)
{
   uintptr_t id = 0;
   struct d3d9_texture_info info;

   info.userdata = video_data;
   info.data     = data;
   info.type     = filter_type;

#ifdef HAVE_THREADS
   if (threaded)
      return video_thread_texture_load(&info,
            d3d9_video_texture_load_wrap_d3d);
#endif

   d3d9_video_texture_load_d3d(&info, &id);
   return id;
}