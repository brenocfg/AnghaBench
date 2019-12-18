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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  intfstream_t ;

/* Variables and functions */
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_HINT_NONE ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_WRITE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intfstream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intfstream_open_file (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rpng_save_image_stream (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned int,unsigned int,int,int) ; 

bool rpng_save_image_argb(const char *path, const uint32_t *data,
      unsigned width, unsigned height, unsigned pitch)
{
   bool ret                      = false;
   intfstream_t* intf_s          = NULL;
   
   intf_s = intfstream_open_file(path, 
         RETRO_VFS_FILE_ACCESS_WRITE,
         RETRO_VFS_FILE_ACCESS_HINT_NONE);

   ret = rpng_save_image_stream((const uint8_t*) data, intf_s,
                                width, height,
                                (signed) pitch, sizeof(uint32_t));
   intfstream_close(intf_s);
   free(intf_s);
   return ret;
}