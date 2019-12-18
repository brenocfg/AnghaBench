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
struct texture_image {int dummy; } ;
typedef  enum texture_filter_type { ____Placeholder_texture_filter_type } texture_filter_type ;
typedef  int /*<<< orphan*/  custom_command_method_t ;

/* Variables and functions */
#define  TEXTURE_FILTER_MIPMAP_LINEAR 129 
#define  TEXTURE_FILTER_MIPMAP_NEAREST 128 
 int /*<<< orphan*/  video_texture_load_gl_core (struct texture_image*,int,uintptr_t*) ; 
 int /*<<< orphan*/  video_texture_load_wrap_gl_core ; 
 int /*<<< orphan*/  video_texture_load_wrap_gl_core_mipmap ; 
 uintptr_t video_thread_texture_load (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uintptr_t gl_core_load_texture(void *video_data, void *data,
                                      bool threaded, enum texture_filter_type filter_type)
{
   uintptr_t id = 0;

#ifdef HAVE_THREADS
   if (threaded)
   {
      custom_command_method_t func = video_texture_load_wrap_gl_core;

      switch (filter_type)
      {
         case TEXTURE_FILTER_MIPMAP_LINEAR:
         case TEXTURE_FILTER_MIPMAP_NEAREST:
            func = video_texture_load_wrap_gl_core_mipmap;
            break;
         default:
            break;
      }
      return video_thread_texture_load(data, func);
   }
#endif

   video_texture_load_gl_core((struct texture_image*)data, filter_type, &id);
   return id;
}