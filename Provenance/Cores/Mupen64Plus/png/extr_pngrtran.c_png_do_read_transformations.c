#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  png_uint_32 ;
typedef  TYPE_1__* png_structrp ;
typedef  TYPE_2__* png_row_infop ;
typedef  scalar_t__ png_byte ;
struct TYPE_37__ {int color_type; scalar_t__ rowbytes; scalar_t__ bit_depth; scalar_t__ channels; int /*<<< orphan*/  width; scalar_t__ pixel_depth; } ;
struct TYPE_36__ {int flags; int transformations; scalar_t__ num_trans; int rgb_to_gray_status; int mode; int color_type; scalar_t__ num_palette_max; scalar_t__ user_transform_depth; scalar_t__ user_transform_channels; int /*<<< orphan*/ * row_buf; int /*<<< orphan*/  (* read_user_transform_fn ) (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ;scalar_t__ filler; int /*<<< orphan*/  shift; int /*<<< orphan*/  quantize_index; int /*<<< orphan*/  palette_lookup; int /*<<< orphan*/  trans_color; int /*<<< orphan*/  trans_alpha; int /*<<< orphan*/  palette; } ;

/* Variables and functions */
 int PNG_16_TO_8 ; 
 int PNG_BACKGROUND_IS_GRAY ; 
 int PNG_BGR ; 
 int PNG_COLOR_MASK_ALPHA ; 
 int PNG_COLOR_TYPE_GRAY_ALPHA ; 
 int PNG_COLOR_TYPE_PALETTE ; 
 int PNG_COLOR_TYPE_RGB_ALPHA ; 
 int PNG_COMPOSE ; 
 int PNG_ENCODE_ALPHA ; 
 int PNG_EXPAND ; 
 int PNG_EXPAND_16 ; 
 int PNG_EXPAND_tRNS ; 
 int PNG_FILLER ; 
 int PNG_FLAG_DETECT_UNINITIALIZED ; 
 int PNG_FLAG_ROW_INIT ; 
 int PNG_GAMMA ; 
 int PNG_GRAY_TO_RGB ; 
 int PNG_INVERT_ALPHA ; 
 int PNG_INVERT_MONO ; 
 int PNG_PACK ; 
 int PNG_PACKSWAP ; 
 int PNG_QUANTIZE ; 
 int PNG_RGB_TO_GRAY ; 
 int PNG_RGB_TO_GRAY_ERR ; 
 int PNG_RGB_TO_GRAY_WARN ; 
 scalar_t__ PNG_ROWBYTES (scalar_t__,int /*<<< orphan*/ ) ; 
 int PNG_SCALE_16_TO_8 ; 
 int PNG_SHIFT ; 
 int PNG_STRIP_ALPHA ; 
 int PNG_SWAP_ALPHA ; 
 int PNG_SWAP_BYTES ; 
 int PNG_USER_TRANSFORM ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_do_bgr (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_do_check_palette_indexes (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  png_do_chop (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_do_compose (TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  png_do_encode_alpha (TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  png_do_expand (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_do_expand_16 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_do_expand_palette (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  png_do_gamma (TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  png_do_gray_to_rgb (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_do_invert (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_do_packswap (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_do_quantize (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_do_read_filler (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  png_do_read_invert_alpha (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_do_read_swap_alpha (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int png_do_rgb_to_gray (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_do_scale_16_to_8 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_do_strip_channel (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_do_swap (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_do_unpack (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_do_unshift (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_warning (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ; 

void /* PRIVATE */
png_do_read_transformations(png_structrp png_ptr, png_row_infop row_info)
{
   png_debug(1, "in png_do_read_transformations");

   if (png_ptr->row_buf == NULL)
   {
      /* Prior to 1.5.4 this output row/pass where the NULL pointer is, but this
       * error is incredibly rare and incredibly easy to debug without this
       * information.
       */
      png_error(png_ptr, "NULL row buffer");
   }

   /* The following is debugging; prior to 1.5.4 the code was never compiled in;
    * in 1.5.4 PNG_FLAG_DETECT_UNINITIALIZED was added and the macro
    * PNG_WARN_UNINITIALIZED_ROW removed.  In 1.6 the new flag is set only for
    * all transformations, however in practice the ROW_INIT always gets done on
    * demand, if necessary.
    */
   if ((png_ptr->flags & PNG_FLAG_DETECT_UNINITIALIZED) != 0 &&
       (png_ptr->flags & PNG_FLAG_ROW_INIT) == 0)
   {
      /* Application has failed to call either png_read_start_image() or
       * png_read_update_info() after setting transforms that expand pixels.
       * This check added to libpng-1.2.19 (but not enabled until 1.5.4).
       */
      png_error(png_ptr, "Uninitialized row");
   }

#ifdef PNG_READ_EXPAND_SUPPORTED
   if ((png_ptr->transformations & PNG_EXPAND) != 0)
   {
      if (row_info->color_type == PNG_COLOR_TYPE_PALETTE)
      {
         png_do_expand_palette(row_info, png_ptr->row_buf + 1,
             png_ptr->palette, png_ptr->trans_alpha, png_ptr->num_trans);
      }

      else
      {
         if (png_ptr->num_trans != 0 &&
             (png_ptr->transformations & PNG_EXPAND_tRNS) != 0)
            png_do_expand(row_info, png_ptr->row_buf + 1,
                &(png_ptr->trans_color));

         else
            png_do_expand(row_info, png_ptr->row_buf + 1,
                NULL);
      }
   }
#endif

#ifdef PNG_READ_STRIP_ALPHA_SUPPORTED
   if ((png_ptr->transformations & PNG_STRIP_ALPHA) != 0 &&
       (png_ptr->transformations & PNG_COMPOSE) == 0 &&
       (row_info->color_type == PNG_COLOR_TYPE_RGB_ALPHA ||
       row_info->color_type == PNG_COLOR_TYPE_GRAY_ALPHA))
      png_do_strip_channel(row_info, png_ptr->row_buf + 1,
          0 /* at_start == false, because SWAP_ALPHA happens later */);
#endif

#ifdef PNG_READ_RGB_TO_GRAY_SUPPORTED
   if ((png_ptr->transformations & PNG_RGB_TO_GRAY) != 0)
   {
      int rgb_error =
          png_do_rgb_to_gray(png_ptr, row_info,
              png_ptr->row_buf + 1);

      if (rgb_error != 0)
      {
         png_ptr->rgb_to_gray_status=1;
         if ((png_ptr->transformations & PNG_RGB_TO_GRAY) ==
             PNG_RGB_TO_GRAY_WARN)
            png_warning(png_ptr, "png_do_rgb_to_gray found nongray pixel");

         if ((png_ptr->transformations & PNG_RGB_TO_GRAY) ==
             PNG_RGB_TO_GRAY_ERR)
            png_error(png_ptr, "png_do_rgb_to_gray found nongray pixel");
      }
   }
#endif

/* From Andreas Dilger e-mail to png-implement, 26 March 1998:
 *
 *   In most cases, the "simple transparency" should be done prior to doing
 *   gray-to-RGB, or you will have to test 3x as many bytes to check if a
 *   pixel is transparent.  You would also need to make sure that the
 *   transparency information is upgraded to RGB.
 *
 *   To summarize, the current flow is:
 *   - Gray + simple transparency -> compare 1 or 2 gray bytes and composite
 *                                   with background "in place" if transparent,
 *                                   convert to RGB if necessary
 *   - Gray + alpha -> composite with gray background and remove alpha bytes,
 *                                   convert to RGB if necessary
 *
 *   To support RGB backgrounds for gray images we need:
 *   - Gray + simple transparency -> convert to RGB + simple transparency,
 *                                   compare 3 or 6 bytes and composite with
 *                                   background "in place" if transparent
 *                                   (3x compare/pixel compared to doing
 *                                   composite with gray bkgrnd)
 *   - Gray + alpha -> convert to RGB + alpha, composite with background and
 *                                   remove alpha bytes (3x float
 *                                   operations/pixel compared with composite
 *                                   on gray background)
 *
 *  Greg's change will do this.  The reason it wasn't done before is for
 *  performance, as this increases the per-pixel operations.  If we would check
 *  in advance if the background was gray or RGB, and position the gray-to-RGB
 *  transform appropriately, then it would save a lot of work/time.
 */

#ifdef PNG_READ_GRAY_TO_RGB_SUPPORTED
   /* If gray -> RGB, do so now only if background is non-gray; else do later
    * for performance reasons
    */
   if ((png_ptr->transformations & PNG_GRAY_TO_RGB) != 0 &&
       (png_ptr->mode & PNG_BACKGROUND_IS_GRAY) == 0)
      png_do_gray_to_rgb(row_info, png_ptr->row_buf + 1);
#endif

#if defined(PNG_READ_BACKGROUND_SUPPORTED) ||\
   defined(PNG_READ_ALPHA_MODE_SUPPORTED)
   if ((png_ptr->transformations & PNG_COMPOSE) != 0)
      png_do_compose(row_info, png_ptr->row_buf + 1, png_ptr);
#endif

#ifdef PNG_READ_GAMMA_SUPPORTED
   if ((png_ptr->transformations & PNG_GAMMA) != 0 &&
#ifdef PNG_READ_RGB_TO_GRAY_SUPPORTED
      /* Because RGB_TO_GRAY does the gamma transform. */
      (png_ptr->transformations & PNG_RGB_TO_GRAY) == 0 &&
#endif
#if defined(PNG_READ_BACKGROUND_SUPPORTED) ||\
   defined(PNG_READ_ALPHA_MODE_SUPPORTED)
      /* Because PNG_COMPOSE does the gamma transform if there is something to
       * do (if there is an alpha channel or transparency.)
       */
       !((png_ptr->transformations & PNG_COMPOSE) != 0 &&
       ((png_ptr->num_trans != 0) ||
       (png_ptr->color_type & PNG_COLOR_MASK_ALPHA) != 0)) &&
#endif
      /* Because png_init_read_transformations transforms the palette, unless
       * RGB_TO_GRAY will do the transform.
       */
       (png_ptr->color_type != PNG_COLOR_TYPE_PALETTE))
      png_do_gamma(row_info, png_ptr->row_buf + 1, png_ptr);
#endif

#ifdef PNG_READ_STRIP_ALPHA_SUPPORTED
   if ((png_ptr->transformations & PNG_STRIP_ALPHA) != 0 &&
       (png_ptr->transformations & PNG_COMPOSE) != 0 &&
       (row_info->color_type == PNG_COLOR_TYPE_RGB_ALPHA ||
       row_info->color_type == PNG_COLOR_TYPE_GRAY_ALPHA))
      png_do_strip_channel(row_info, png_ptr->row_buf + 1,
          0 /* at_start == false, because SWAP_ALPHA happens later */);
#endif

#ifdef PNG_READ_ALPHA_MODE_SUPPORTED
   if ((png_ptr->transformations & PNG_ENCODE_ALPHA) != 0 &&
       (row_info->color_type & PNG_COLOR_MASK_ALPHA) != 0)
      png_do_encode_alpha(row_info, png_ptr->row_buf + 1, png_ptr);
#endif

#ifdef PNG_READ_SCALE_16_TO_8_SUPPORTED
   if ((png_ptr->transformations & PNG_SCALE_16_TO_8) != 0)
      png_do_scale_16_to_8(row_info, png_ptr->row_buf + 1);
#endif

#ifdef PNG_READ_STRIP_16_TO_8_SUPPORTED
   /* There is no harm in doing both of these because only one has any effect,
    * by putting the 'scale' option first if the app asks for scale (either by
    * calling the API or in a TRANSFORM flag) this is what happens.
    */
   if ((png_ptr->transformations & PNG_16_TO_8) != 0)
      png_do_chop(row_info, png_ptr->row_buf + 1);
#endif

#ifdef PNG_READ_QUANTIZE_SUPPORTED
   if ((png_ptr->transformations & PNG_QUANTIZE) != 0)
   {
      png_do_quantize(row_info, png_ptr->row_buf + 1,
          png_ptr->palette_lookup, png_ptr->quantize_index);

      if (row_info->rowbytes == 0)
         png_error(png_ptr, "png_do_quantize returned rowbytes=0");
   }
#endif /* READ_QUANTIZE */

#ifdef PNG_READ_EXPAND_16_SUPPORTED
   /* Do the expansion now, after all the arithmetic has been done.  Notice
    * that previous transformations can handle the PNG_EXPAND_16 flag if this
    * is efficient (particularly true in the case of gamma correction, where
    * better accuracy results faster!)
    */
   if ((png_ptr->transformations & PNG_EXPAND_16) != 0)
      png_do_expand_16(row_info, png_ptr->row_buf + 1);
#endif

#ifdef PNG_READ_GRAY_TO_RGB_SUPPORTED
   /* NOTE: moved here in 1.5.4 (from much later in this list.) */
   if ((png_ptr->transformations & PNG_GRAY_TO_RGB) != 0 &&
       (png_ptr->mode & PNG_BACKGROUND_IS_GRAY) != 0)
      png_do_gray_to_rgb(row_info, png_ptr->row_buf + 1);
#endif

#ifdef PNG_READ_INVERT_SUPPORTED
   if ((png_ptr->transformations & PNG_INVERT_MONO) != 0)
      png_do_invert(row_info, png_ptr->row_buf + 1);
#endif

#ifdef PNG_READ_INVERT_ALPHA_SUPPORTED
   if ((png_ptr->transformations & PNG_INVERT_ALPHA) != 0)
      png_do_read_invert_alpha(row_info, png_ptr->row_buf + 1);
#endif

#ifdef PNG_READ_SHIFT_SUPPORTED
   if ((png_ptr->transformations & PNG_SHIFT) != 0)
      png_do_unshift(row_info, png_ptr->row_buf + 1,
          &(png_ptr->shift));
#endif

#ifdef PNG_READ_PACK_SUPPORTED
   if ((png_ptr->transformations & PNG_PACK) != 0)
      png_do_unpack(row_info, png_ptr->row_buf + 1);
#endif

#ifdef PNG_READ_CHECK_FOR_INVALID_INDEX_SUPPORTED
   /* Added at libpng-1.5.10 */
   if (row_info->color_type == PNG_COLOR_TYPE_PALETTE &&
       png_ptr->num_palette_max >= 0)
      png_do_check_palette_indexes(png_ptr, row_info);
#endif

#ifdef PNG_READ_BGR_SUPPORTED
   if ((png_ptr->transformations & PNG_BGR) != 0)
      png_do_bgr(row_info, png_ptr->row_buf + 1);
#endif

#ifdef PNG_READ_PACKSWAP_SUPPORTED
   if ((png_ptr->transformations & PNG_PACKSWAP) != 0)
      png_do_packswap(row_info, png_ptr->row_buf + 1);
#endif

#ifdef PNG_READ_FILLER_SUPPORTED
   if ((png_ptr->transformations & PNG_FILLER) != 0)
      png_do_read_filler(row_info, png_ptr->row_buf + 1,
          (png_uint_32)png_ptr->filler, png_ptr->flags);
#endif

#ifdef PNG_READ_SWAP_ALPHA_SUPPORTED
   if ((png_ptr->transformations & PNG_SWAP_ALPHA) != 0)
      png_do_read_swap_alpha(row_info, png_ptr->row_buf + 1);
#endif

#ifdef PNG_READ_16BIT_SUPPORTED
#ifdef PNG_READ_SWAP_SUPPORTED
   if ((png_ptr->transformations & PNG_SWAP_BYTES) != 0)
      png_do_swap(row_info, png_ptr->row_buf + 1);
#endif
#endif

#ifdef PNG_READ_USER_TRANSFORM_SUPPORTED
   if ((png_ptr->transformations & PNG_USER_TRANSFORM) != 0)
   {
      if (png_ptr->read_user_transform_fn != NULL)
         (*(png_ptr->read_user_transform_fn)) /* User read transform function */
             (png_ptr,     /* png_ptr */
             row_info,     /* row_info: */
                /*  png_uint_32 width;       width of row */
                /*  png_size_t rowbytes;     number of bytes in row */
                /*  png_byte color_type;     color type of pixels */
                /*  png_byte bit_depth;      bit depth of samples */
                /*  png_byte channels;       number of channels (1-4) */
                /*  png_byte pixel_depth;    bits per pixel (depth*channels) */
             png_ptr->row_buf + 1);    /* start of pixel data for row */
#ifdef PNG_USER_TRANSFORM_PTR_SUPPORTED
      if (png_ptr->user_transform_depth != 0)
         row_info->bit_depth = png_ptr->user_transform_depth;

      if (png_ptr->user_transform_channels != 0)
         row_info->channels = png_ptr->user_transform_channels;
#endif
      row_info->pixel_depth = (png_byte)(row_info->bit_depth *
          row_info->channels);

      row_info->rowbytes = PNG_ROWBYTES(row_info->pixel_depth, row_info->width);
   }
#endif
}