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
struct display {int options; int h; scalar_t__ ct; int bpp; int size; char* operation; int /*<<< orphan*/ * ip; int /*<<< orphan*/ * read_pp; int /*<<< orphan*/  w; } ;
typedef  TYPE_1__* png_colorp ;
struct TYPE_5__ {int red; int green; int blue; } ;
typedef  TYPE_1__ png_color ;
typedef  int png_alloc_size_t ;

/* Variables and functions */
 int FIX_INDEX ; 
 int IGNORE_INDEX ; 
 int /*<<< orphan*/  LIBPNG_ERROR ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  PNGCP_TIME_READ ; 
 scalar_t__ PNG_COLOR_TYPE_PALETTE ; 
 int /*<<< orphan*/  PNG_HANDLE_CHUNK_ALWAYS ; 
 scalar_t__ PNG_INFO_PLTE ; 
 int /*<<< orphan*/  PNG_LIBPNG_VER_STRING ; 
 int /*<<< orphan*/  display_clean_read (struct display*) ; 
 int /*<<< orphan*/  display_error ; 
 int /*<<< orphan*/  display_log (struct display*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  display_start_read (struct display*,char const*) ; 
 int /*<<< orphan*/  display_warning ; 
 int /*<<< orphan*/  end_timer (struct display*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * png_create_info_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * png_create_read_struct (int /*<<< orphan*/ ,struct display*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ png_get_PLTE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**,int*) ; 
 int png_get_bit_depth (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int png_get_channels (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ png_get_color_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int png_get_image_height (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_get_image_width (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int png_get_palette_max (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int png_get_rowbytes (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_read_png (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_set_PLTE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  png_set_benign_errors (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  png_set_check_for_invalid_index (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  png_set_keep_unknown_chunks (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_set_read_fn (int /*<<< orphan*/ *,struct display*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_set_user_limits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  read_function ; 
 int /*<<< orphan*/  start_timer (struct display*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
read_png(struct display *dp, const char *filename)
{
   display_clean_read(dp); /* safety */
   display_start_read(dp, filename);

   dp->read_pp = png_create_read_struct(PNG_LIBPNG_VER_STRING, dp,
      display_error, display_warning);
   if (dp->read_pp == NULL)
      display_log(dp, LIBPNG_ERROR, "failed to create read struct");

#  ifdef PNG_BENIGN_ERRORS_SUPPORTED
      png_set_benign_errors(dp->read_pp, 1/*allowed*/);
#  endif /* BENIGN_ERRORS */

#  ifdef FIX_INDEX
      if ((dp->options & FIX_INDEX) != 0)
         png_set_check_for_invalid_index(dp->read_pp, 1/*on, no warning*/);
#     ifdef IGNORE_INDEX
         else
#     endif /* IGNORE_INDEX */
#  endif /* FIX_INDEX */
#  ifdef IGNORE_INDEX
      if ((dp->options & IGNORE_INDEX) != 0) /* DANGEROUS */
         png_set_check_for_invalid_index(dp->read_pp, -1/*off completely*/);
#  endif /* IGNORE_INDEX */

   /* The png_read_png API requires us to make the info struct, but it does the
    * call to png_read_info.
    */
   dp->ip = png_create_info_struct(dp->read_pp);
   if (dp->ip == NULL)
      png_error(dp->read_pp, "failed to create info struct");

   /* Set the IO handling */
   png_set_read_fn(dp->read_pp, dp, read_function);

#  ifdef PNG_HANDLE_AS_UNKNOWN_SUPPORTED
      png_set_keep_unknown_chunks(dp->read_pp, PNG_HANDLE_CHUNK_ALWAYS, NULL,
            0);
#  endif /* HANDLE_AS_UNKNOWN */

#  ifdef PNG_SET_USER_LIMITS_SUPPORTED
      /* Remove the user limits, if any */
      png_set_user_limits(dp->read_pp, 0x7fffffff, 0x7fffffff);
#  endif /* SET_USER_LIMITS */

   /* Now read the PNG. */
   start_timer(dp, PNGCP_TIME_READ);
   png_read_png(dp->read_pp, dp->ip, 0U/*transforms*/, NULL/*params*/);
   end_timer(dp, PNGCP_TIME_READ);
   dp->w = png_get_image_width(dp->read_pp, dp->ip);
   dp->h = png_get_image_height(dp->read_pp, dp->ip);
   dp->ct = png_get_color_type(dp->read_pp, dp->ip);
   dp->bpp = png_get_bit_depth(dp->read_pp, dp->ip) *
             png_get_channels(dp->read_pp, dp->ip);
   {
      /* png_get_rowbytes should never return 0 because the value is set by the
       * first call to png_set_IHDR, which should have happened by now, but just
       * in case:
       */
      png_alloc_size_t rb = png_get_rowbytes(dp->read_pp, dp->ip);

      if (rb == 0)
         png_error(dp->read_pp, "invalid row byte count from libpng");

      /* The size calc can overflow. */
      if ((MAX_SIZE-dp->h)/rb < dp->h)
         png_error(dp->read_pp, "image too large");

      dp->size = rb * dp->h + dp->h/*filter byte*/;
   }

#ifdef FIX_INDEX
   if (dp->ct == PNG_COLOR_TYPE_PALETTE && (dp->options & FIX_INDEX) != 0)
   {
      int max = png_get_palette_max(dp->read_pp, dp->ip);
      png_colorp palette = NULL;
      int num = -1;

      if (png_get_PLTE(dp->read_pp, dp->ip, &palette, &num) != PNG_INFO_PLTE
          || max < 0 || num <= 0 || palette == NULL)
         display_log(dp, LIBPNG_ERROR, "invalid png_get_PLTE result");

      if (max >= num)
      {
         /* 'Fix' the palette. */
         int i;
         png_color newpal[256];

         for (i=0; i<num; ++i)
            newpal[i] = palette[i];

         /* Fill in any remainder with a warning color: */
         for (; i<=max; ++i)
         {
            newpal[i].red = 0xbe;
            newpal[i].green = 0xad;
            newpal[i].blue = 0xed;
         }

         png_set_PLTE(dp->read_pp, dp->ip, newpal, i);
      }
   }
#endif /* FIX_INDEX */

   display_clean_read(dp);
   dp->operation = "none";
}