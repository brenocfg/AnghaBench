#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uLong ;
typedef  scalar_t__ png_uint_32 ;
typedef  TYPE_1__* png_const_structrp ;
typedef  int /*<<< orphan*/ * png_const_bytep ;
struct TYPE_6__ {scalar_t__* md5; scalar_t__ have_md5; int is_broken; scalar_t__ adler; scalar_t__ crc; scalar_t__ intent; scalar_t__ length; } ;
struct TYPE_5__ {int options; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_CHUNK_ERROR ; 
 int /*<<< orphan*/  PNG_CHUNK_WARNING ; 
 int PNG_OPTION_ON ; 
 int PNG_SKIP_sRGB_CHECK_PROFILE ; 
 scalar_t__ adler32 (scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ crc32 (scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  png_chunk_report (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ png_get_uint_32 (int /*<<< orphan*/ *) ; 
 TYPE_2__* png_sRGB_checks ; 

__attribute__((used)) static int
png_compare_ICC_profile_with_sRGB(png_const_structrp png_ptr,
    png_const_bytep profile, uLong adler)
{
   /* The quick check is to verify just the MD5 signature and trust the
    * rest of the data.  Because the profile has already been verified for
    * correctness this is safe.  png_colorspace_set_sRGB will check the 'intent'
    * field too, so if the profile has been edited with an intent not defined
    * by sRGB (but maybe defined by a later ICC specification) the read of
    * the profile will fail at that point.
    */

   png_uint_32 length = 0;
   png_uint_32 intent = 0x10000; /* invalid */
#if PNG_sRGB_PROFILE_CHECKS > 1
   uLong crc = 0; /* the value for 0 length data */
#endif
   unsigned int i;

#ifdef PNG_SET_OPTION_SUPPORTED
   /* First see if PNG_SKIP_sRGB_CHECK_PROFILE has been set to "on" */
   if (((png_ptr->options >> PNG_SKIP_sRGB_CHECK_PROFILE) & 3) ==
               PNG_OPTION_ON)
      return 0;
#endif

   for (i=0; i < (sizeof png_sRGB_checks) / (sizeof png_sRGB_checks[0]); ++i)
   {
      if (png_get_uint_32(profile+84) == png_sRGB_checks[i].md5[0] &&
         png_get_uint_32(profile+88) == png_sRGB_checks[i].md5[1] &&
         png_get_uint_32(profile+92) == png_sRGB_checks[i].md5[2] &&
         png_get_uint_32(profile+96) == png_sRGB_checks[i].md5[3])
      {
         /* This may be one of the old HP profiles without an MD5, in that
          * case we can only use the length and Adler32 (note that these
          * are not used by default if there is an MD5!)
          */
#        if PNG_sRGB_PROFILE_CHECKS == 0
            if (png_sRGB_checks[i].have_md5 != 0)
               return 1+png_sRGB_checks[i].is_broken;
#        endif

         /* Profile is unsigned or more checks have been configured in. */
         if (length == 0)
         {
            length = png_get_uint_32(profile);
            intent = png_get_uint_32(profile+64);
         }

         /* Length *and* intent must match */
         if (length == (png_uint_32) png_sRGB_checks[i].length &&
            intent == (png_uint_32) png_sRGB_checks[i].intent)
         {
            /* Now calculate the adler32 if not done already. */
            if (adler == 0)
            {
               adler = adler32(0, NULL, 0);
               adler = adler32(adler, profile, length);
            }

            if (adler == png_sRGB_checks[i].adler)
            {
               /* These basic checks suggest that the data has not been
                * modified, but if the check level is more than 1 perform
                * our own crc32 checksum on the data.
                */
#              if PNG_sRGB_PROFILE_CHECKS > 1
                  if (crc == 0)
                  {
                     crc = crc32(0, NULL, 0);
                     crc = crc32(crc, profile, length);
                  }

                  /* So this check must pass for the 'return' below to happen.
                   */
                  if (crc == png_sRGB_checks[i].crc)
#              endif
               {
                  if (png_sRGB_checks[i].is_broken != 0)
                  {
                     /* These profiles are known to have bad data that may cause
                      * problems if they are used, therefore attempt to
                      * discourage their use, skip the 'have_md5' warning below,
                      * which is made irrelevant by this error.
                      */
                     png_chunk_report(png_ptr, "known incorrect sRGB profile",
                         PNG_CHUNK_ERROR);
                  }

                  /* Warn that this being done; this isn't even an error since
                   * the profile is perfectly valid, but it would be nice if
                   * people used the up-to-date ones.
                   */
                  else if (png_sRGB_checks[i].have_md5 == 0)
                  {
                     png_chunk_report(png_ptr,
                         "out-of-date sRGB profile with no signature",
                         PNG_CHUNK_WARNING);
                  }

                  return 1+png_sRGB_checks[i].is_broken;
               }
            }

# if PNG_sRGB_PROFILE_CHECKS > 0
         /* The signature matched, but the profile had been changed in some
          * way.  This probably indicates a data error or uninformed hacking.
          * Fall through to "no match".
          */
         png_chunk_report(png_ptr,
             "Not recognizing known sRGB profile that has been edited",
             PNG_CHUNK_WARNING);
         break;
# endif
         }
      }
   }

   return 0; /* no match */
}