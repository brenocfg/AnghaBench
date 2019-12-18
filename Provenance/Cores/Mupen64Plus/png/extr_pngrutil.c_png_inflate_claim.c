#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ png_uint_32 ;
typedef  TYPE_1__* png_structrp ;
struct TYPE_12__ {scalar_t__ avail_out; int /*<<< orphan*/ * next_out; scalar_t__ avail_in; int /*<<< orphan*/ * next_in; } ;
struct TYPE_11__ {scalar_t__ zowner; int options; int zstream_start; int flags; TYPE_6__ zstream; } ;

/* Variables and functions */
 int PNG_FLAG_CRC_CRITICAL_IGNORE ; 
 int PNG_FLAG_ZSTREAM_INITIALIZED ; 
 int PNG_MAXIMUM_INFLATE_WINDOW ; 
 int PNG_OPTION_ON ; 
 int /*<<< orphan*/  PNG_STRING_FROM_CHUNK (char*,scalar_t__) ; 
 int Z_OK ; 
 int inflateInit (TYPE_6__*) ; 
 int inflateInit2 (TYPE_6__*,int) ; 
 int inflateReset (TYPE_6__*) ; 
 int inflateReset2 (TYPE_6__*,int) ; 
 int inflateValidate (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_chunk_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_chunk_warning (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_safecat (char*,int,int,char*) ; 
 int /*<<< orphan*/  png_zstream_error (TYPE_1__*,int) ; 

__attribute__((used)) static int
png_inflate_claim(png_structrp png_ptr, png_uint_32 owner)
{
   if (png_ptr->zowner != 0)
   {
      char msg[64];

      PNG_STRING_FROM_CHUNK(msg, png_ptr->zowner);
      /* So the message that results is "<chunk> using zstream"; this is an
       * internal error, but is very useful for debugging.  i18n requirements
       * are minimal.
       */
      (void)png_safecat(msg, (sizeof msg), 4, " using zstream");
#if PNG_RELEASE_BUILD
      png_chunk_warning(png_ptr, msg);
      png_ptr->zowner = 0;
#else
      png_chunk_error(png_ptr, msg);
#endif
   }

   /* Implementation note: unlike 'png_deflate_claim' this internal function
    * does not take the size of the data as an argument.  Some efficiency could
    * be gained by using this when it is known *if* the zlib stream itself does
    * not record the number; however, this is an illusion: the original writer
    * of the PNG may have selected a lower window size, and we really must
    * follow that because, for systems with with limited capabilities, we
    * would otherwise reject the application's attempts to use a smaller window
    * size (zlib doesn't have an interface to say "this or lower"!).
    *
    * inflateReset2 was added to zlib 1.2.4; before this the window could not be
    * reset, therefore it is necessary to always allocate the maximum window
    * size with earlier zlibs just in case later compressed chunks need it.
    */
   {
      int ret; /* zlib return code */
#if ZLIB_VERNUM >= 0x1240
      int window_bits = 0;

# if defined(PNG_SET_OPTION_SUPPORTED) && defined(PNG_MAXIMUM_INFLATE_WINDOW)
      if (((png_ptr->options >> PNG_MAXIMUM_INFLATE_WINDOW) & 3) ==
          PNG_OPTION_ON)
      {
         window_bits = 15;
         png_ptr->zstream_start = 0; /* fixed window size */
      }

      else
      {
         png_ptr->zstream_start = 1;
      }
# endif

#endif /* ZLIB_VERNUM >= 0x1240 */

      /* Set this for safety, just in case the previous owner left pointers to
       * memory allocations.
       */
      png_ptr->zstream.next_in = NULL;
      png_ptr->zstream.avail_in = 0;
      png_ptr->zstream.next_out = NULL;
      png_ptr->zstream.avail_out = 0;

      if ((png_ptr->flags & PNG_FLAG_ZSTREAM_INITIALIZED) != 0)
      {
#if ZLIB_VERNUM >= 0x1240
         ret = inflateReset2(&png_ptr->zstream, window_bits);
#else
         ret = inflateReset(&png_ptr->zstream);
#endif
      }

      else
      {
#if ZLIB_VERNUM >= 0x1240
         ret = inflateInit2(&png_ptr->zstream, window_bits);
#else
         ret = inflateInit(&png_ptr->zstream);
#endif

         if (ret == Z_OK)
            png_ptr->flags |= PNG_FLAG_ZSTREAM_INITIALIZED;
      }

#if ZLIB_VERNUM >= 0x1281
      /* Turn off validation of the ADLER32 checksum */
      if ((png_ptr->flags & PNG_FLAG_CRC_CRITICAL_IGNORE) != 0)
         ret = inflateValidate(&png_ptr->zstream, 0);
#endif

      if (ret == Z_OK)
         png_ptr->zowner = owner;

      else
         png_zstream_error(png_ptr, ret);

      return ret;
   }

#ifdef window_bits
# undef window_bits
#endif
}