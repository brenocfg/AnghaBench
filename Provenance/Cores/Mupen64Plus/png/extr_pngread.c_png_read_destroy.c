#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* png_structrp ;
struct TYPE_7__ {int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {int free_me; int /*<<< orphan*/ * chunk_list; TYPE_1__ unknown_chunk; int /*<<< orphan*/ * save_buffer; int /*<<< orphan*/  zstream; int /*<<< orphan*/ * trans_alpha; int /*<<< orphan*/ * palette; int /*<<< orphan*/ * quantize_index; int /*<<< orphan*/ * palette_lookup; int /*<<< orphan*/ * read_buffer; int /*<<< orphan*/ * big_prev_row; int /*<<< orphan*/ * big_row_buf; } ;

/* Variables and functions */
 int PNG_FREE_PLTE ; 
 int PNG_FREE_TRNS ; 
 int /*<<< orphan*/  inflateEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_destroy_gamma_table (TYPE_2__*) ; 
 int /*<<< orphan*/  png_free (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_zfree (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
png_read_destroy(png_structrp png_ptr)
{
   png_debug(1, "in png_read_destroy");

#ifdef PNG_READ_GAMMA_SUPPORTED
   png_destroy_gamma_table(png_ptr);
#endif

   png_free(png_ptr, png_ptr->big_row_buf);
   png_ptr->big_row_buf = NULL;
   png_free(png_ptr, png_ptr->big_prev_row);
   png_ptr->big_prev_row = NULL;
   png_free(png_ptr, png_ptr->read_buffer);
   png_ptr->read_buffer = NULL;

#ifdef PNG_READ_QUANTIZE_SUPPORTED
   png_free(png_ptr, png_ptr->palette_lookup);
   png_ptr->palette_lookup = NULL;
   png_free(png_ptr, png_ptr->quantize_index);
   png_ptr->quantize_index = NULL;
#endif

   if ((png_ptr->free_me & PNG_FREE_PLTE) != 0)
   {
      png_zfree(png_ptr, png_ptr->palette);
      png_ptr->palette = NULL;
   }
   png_ptr->free_me &= ~PNG_FREE_PLTE;

#if defined(PNG_tRNS_SUPPORTED) || \
    defined(PNG_READ_EXPAND_SUPPORTED) || defined(PNG_READ_BACKGROUND_SUPPORTED)
   if ((png_ptr->free_me & PNG_FREE_TRNS) != 0)
   {
      png_free(png_ptr, png_ptr->trans_alpha);
      png_ptr->trans_alpha = NULL;
   }
   png_ptr->free_me &= ~PNG_FREE_TRNS;
#endif

   inflateEnd(&png_ptr->zstream);

#ifdef PNG_PROGRESSIVE_READ_SUPPORTED
   png_free(png_ptr, png_ptr->save_buffer);
   png_ptr->save_buffer = NULL;
#endif

#if defined(PNG_STORE_UNKNOWN_CHUNKS_SUPPORTED) && \
   defined(PNG_READ_UNKNOWN_CHUNKS_SUPPORTED)
   png_free(png_ptr, png_ptr->unknown_chunk.data);
   png_ptr->unknown_chunk.data = NULL;
#endif

#ifdef PNG_SET_UNKNOWN_CHUNKS_SUPPORTED
   png_free(png_ptr, png_ptr->chunk_list);
   png_ptr->chunk_list = NULL;
#endif

   /* NOTE: the 'setjmp' buffer may still be allocated and the memory and error
    * callbacks are still set at this point.  They are required to complete the
    * destruction of the png_struct itself.
    */
}