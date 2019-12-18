#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_structrp ;
struct TYPE_5__ {int flags; int /*<<< orphan*/ * chunk_list; int /*<<< orphan*/ * tst_row; int /*<<< orphan*/ * try_row; int /*<<< orphan*/ * prev_row; int /*<<< orphan*/ * row_buf; int /*<<< orphan*/  zbuffer_list; int /*<<< orphan*/  zstream; } ;

/* Variables and functions */
 int PNG_FLAG_ZSTREAM_INITIALIZED ; 
 int /*<<< orphan*/  deflateEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_free_buffer_list (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
png_write_destroy(png_structrp png_ptr)
{
   png_debug(1, "in png_write_destroy");

   /* Free any memory zlib uses */
   if ((png_ptr->flags & PNG_FLAG_ZSTREAM_INITIALIZED) != 0)
      deflateEnd(&png_ptr->zstream);

   /* Free our memory.  png_free checks NULL for us. */
   png_free_buffer_list(png_ptr, &png_ptr->zbuffer_list);
   png_free(png_ptr, png_ptr->row_buf);
   png_ptr->row_buf = NULL;
#ifdef PNG_WRITE_FILTER_SUPPORTED
   png_free(png_ptr, png_ptr->prev_row);
   png_free(png_ptr, png_ptr->try_row);
   png_free(png_ptr, png_ptr->tst_row);
   png_ptr->prev_row = NULL;
   png_ptr->try_row = NULL;
   png_ptr->tst_row = NULL;
#endif

#ifdef PNG_SET_UNKNOWN_CHUNKS_SUPPORTED
   png_free(png_ptr, png_ptr->chunk_list);
   png_ptr->chunk_list = NULL;
#endif

   /* The error handling and memory handling information is left intact at this
    * point: the jmp_buf may still have to be freed.  See png_destroy_png_struct
    * for how this happens.
    */
}