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
typedef  int /*<<< orphan*/ * png_structrp ;
typedef  int /*<<< orphan*/  png_struct ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  png_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_free_jmpbuf (int /*<<< orphan*/ *) ; 

void /* PRIVATE */
png_destroy_png_struct(png_structrp png_ptr)
{
   if (png_ptr != NULL)
   {
      /* png_free might call png_error and may certainly call
       * png_get_mem_ptr, so fake a temporary png_struct to support this.
       */
      png_struct dummy_struct = *png_ptr;
      memset(png_ptr, 0, (sizeof *png_ptr));
      png_free(&dummy_struct, png_ptr);

#     ifdef PNG_SETJMP_SUPPORTED
         /* We may have a jmp_buf left to deallocate. */
         png_free_jmpbuf(&dummy_struct);
#     endif
   }
}