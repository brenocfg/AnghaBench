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
struct display {int options; unsigned int write_size; char* operation; int /*<<< orphan*/ * fp; int /*<<< orphan*/  ip; int /*<<< orphan*/ * write_pp; scalar_t__ csp; scalar_t__ nsp; scalar_t__ tsp; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  APP_ERROR ; 
 int IGNORE_INDEX ; 
 int /*<<< orphan*/  LIBPNG_ERROR ; 
 int /*<<< orphan*/  PNGCP_TIME_WRITE ; 
 int /*<<< orphan*/  PNG_FILTER_TYPE_BASE ; 
 int /*<<< orphan*/  PNG_HANDLE_CHUNK_ALWAYS ; 
 int /*<<< orphan*/  PNG_LIBPNG_VER_STRING ; 
 int SEARCH ; 
 int /*<<< orphan*/  display_clean_write (struct display*) ; 
 int /*<<< orphan*/  display_error ; 
 int /*<<< orphan*/  display_log (struct display*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  display_start_write (struct display*,char const*) ; 
 int /*<<< orphan*/  display_warning ; 
 int /*<<< orphan*/  end_timer (struct display*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ get_option (struct display*,char*,int*) ; 
 scalar_t__ getallopts (struct display*,char*,int*) ; 
 int /*<<< orphan*/ * png_create_write_struct (int /*<<< orphan*/ ,struct display*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_set_ICC_profile_compression (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  png_set_IDAT_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  png_set_benign_errors (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  png_set_check_for_invalid_index (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  png_set_compression (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  png_set_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  png_set_keep_unknown_chunks (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_set_text_compression (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  png_set_user_limits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  png_set_write_fn (int /*<<< orphan*/ *,struct display*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_write_png (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  search_compression (struct display*) ; 
 int /*<<< orphan*/  set_ICC_profile_compression (struct display*) ; 
 int /*<<< orphan*/  set_compression (struct display*) ; 
 int /*<<< orphan*/  set_text_compression (struct display*) ; 
 int /*<<< orphan*/  start_timer (struct display*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  text_restore (struct display*) ; 
 int /*<<< orphan*/  write_function ; 

__attribute__((used)) static void
write_png(struct display *dp, const char *destname)
{
   display_clean_write(dp); /* safety */
   display_start_write(dp, destname);

   dp->write_pp = png_create_write_struct(PNG_LIBPNG_VER_STRING, dp,
      display_error, display_warning);

   if (dp->write_pp == NULL)
      display_log(dp, LIBPNG_ERROR, "failed to create write png_struct");

#  ifdef PNG_BENIGN_ERRORS_SUPPORTED
      png_set_benign_errors(dp->write_pp, 1/*allowed*/);
#  endif /* BENIGN_ERRORS */

   png_set_write_fn(dp->write_pp, dp, write_function, NULL/*flush*/);

#ifdef IGNORE_INDEX
   if ((dp->options & IGNORE_INDEX) != 0) /* DANGEROUS */
      png_set_check_for_invalid_index(dp->write_pp, -1/*off completely*/);
#endif /* IGNORE_INDEX */

   /* Restore the text chunks when using libpng 1.6 or less; this is a macro
    * which expands to nothing in 1.7+  In earlier versions it tests
    * dp->text_stashed, which is only set (below) *after* the first write.
    */
   text_restore(dp);

#  ifdef PNG_HANDLE_AS_UNKNOWN_SUPPORTED
      png_set_keep_unknown_chunks(dp->write_pp, PNG_HANDLE_CHUNK_ALWAYS, NULL,
            0);
#  endif /* HANDLE_AS_UNKNOWN */

#  ifdef PNG_SET_USER_LIMITS_SUPPORTED
      /* Remove the user limits, if any */
      png_set_user_limits(dp->write_pp, 0x7fffffff, 0x7fffffff);
#  endif

   /* OPTION HANDLING */
   /* compression outputs, IDAT and zTXt/iTXt: */
   dp->tsp = dp->nsp;
   dp->nsp = dp->csp = 0;
#  ifdef PNG_SW_COMPRESS_png_level
      {
         int val;

         /* This sets everything, but then the following options just override
          * the specific settings for ICC profiles and text.
          */
         if (getallopts(dp, "compression", &val))
            png_set_compression(dp->write_pp, val);

         if (getallopts(dp, "ICC-profile-compression", &val))
            png_set_ICC_profile_compression(dp->write_pp, val);

         if (getallopts(dp, "text-compression", &val))
            png_set_text_compression(dp->write_pp, val);
      }
#  endif /* png_level support */
   if (dp->options & SEARCH)
      search_compression(dp);
   else
      set_compression(dp);
   set_ICC_profile_compression(dp);
   set_text_compression(dp);

   {
      int val;

      /* The permitted range is 1..0x7FFFFFFF, so the cast is safe */
      if (get_option(dp, "IDAT-size", &val))
         png_set_IDAT_size(dp->write_pp, val);
   }

   /* filter handling */
#  ifdef PNG_WRITE_FILTER_SUPPORTED
      {
         int val;

         if (get_option(dp, "filter", &val))
            png_set_filter(dp->write_pp, PNG_FILTER_TYPE_BASE, val);
      }
#  endif /* WRITE_FILTER */

   /* This just uses the 'read' info_struct directly, it contains the image. */
   dp->write_size = 0U;
   start_timer(dp, PNGCP_TIME_WRITE);
   png_write_png(dp->write_pp, dp->ip, 0U/*transforms*/, NULL/*params*/);
   end_timer(dp, PNGCP_TIME_WRITE);

   /* Make sure the file was written ok: */
   if (dp->fp != NULL)
   {
      FILE *fp = dp->fp;
      dp->fp = NULL;
      if (fclose(fp))
         display_log(dp, APP_ERROR, "%s: write failed (%s)",
               destname == NULL ? "stdout" : destname, strerror(errno));
   }

   /* Clean it on the way out - if control returns to the caller then the
    * written_file contains the required data.
    */
   display_clean_write(dp);
   dp->operation = "none";
}