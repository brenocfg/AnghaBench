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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int supports_rgba; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ pixels; } ;
typedef  int /*<<< orphan*/  RFILE ;

/* Variables and functions */
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_HINT_NONE ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_READ ; 
 int /*<<< orphan*/  filestream_close (int /*<<< orphan*/ *) ; 
 size_t filestream_get_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * filestream_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filestream_read (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/ * image_buffer ; 
 int /*<<< orphan*/  image_height ; 
 TYPE_1__ image_texture ; 
 int /*<<< orphan*/  image_texture_load (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  image_width ; 
 int /*<<< orphan*/  imageviewer_free_image () ; 
 void* malloc (size_t) ; 
 int process_new_image ; 
 scalar_t__ stbi_load_from_memory (void*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static bool imageviewer_load(const char *path, int image_index)
{
#ifdef STB_IMAGE_IMPLEMENTATION
   int comp;
   RFILE* f;
   size_t len;
   void* buf;
#endif
#ifdef RARCH_INTERNAL
   extern bool video_driver_supports_rgba(void);
#endif

   imageviewer_free_image();

#ifdef STB_IMAGE_IMPLEMENTATION
   f = filestream_open(path, RETRO_VFS_FILE_ACCESS_READ, RETRO_VFS_FILE_ACCESS_HINT_NONE);
   len = filestream_get_size(f);
   buf = malloc(len);
   filestream_read(f, buf, len);
   filestream_close(f);

   image_buffer           = (uint32_t*)stbi_load_from_memory(
         buf, len,
         &image_width, &image_height,
         &comp, 4);
   free(buf);
#else
#ifdef RARCH_INTERNAL
   image_texture.supports_rgba = video_driver_supports_rgba();
#endif
   if (!image_texture_load(&image_texture, path))
      return false;
   image_buffer = (uint32_t*)image_texture.pixels;
   image_width  = image_texture.width;
   image_height = image_texture.height;
#endif
   if (!image_buffer)
      return false;

   process_new_image = true;

   return true;
}