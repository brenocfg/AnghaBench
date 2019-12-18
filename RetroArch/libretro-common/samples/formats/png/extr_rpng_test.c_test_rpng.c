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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  Imlib_Image ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  imlib_context_set_image (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imlib_free_image () ; 
 int* imlib_image_get_data_for_reading_only () ; 
 unsigned int imlib_image_get_width () ; 
 int /*<<< orphan*/  imlib_load_image (char const*) ; 
 scalar_t__ memcmp (int const*,int*,unsigned int) ; 
 int /*<<< orphan*/  rpng_load_image_argb (char const*,int**,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  rpng_save_image_argb (char*,int const*,int,int,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int test_rpng(const char *in_path)
{
#ifdef HAVE_IMLIB2
   Imlib_Image img;
   const uint32_t *imlib_data = NULL;
#endif
   const uint32_t test_data[] = {
      0xff000000 | 0x50, 0xff000000 | 0x80,
      0xff000000 | 0x40, 0xff000000 | 0x88,
      0xff000000 | 0x50, 0xff000000 | 0x80,
      0xff000000 | 0x40, 0xff000000 | 0x88,
      0xff000000 | 0xc3, 0xff000000 | 0xd3,
      0xff000000 | 0xc3, 0xff000000 | 0xd3,
      0xff000000 | 0xc3, 0xff000000 | 0xd3,
      0xff000000 | 0xc3, 0xff000000 | 0xd3,
   };
   uint32_t *data = NULL;
   unsigned width = 0;
   unsigned height = 0;

   if (!rpng_save_image_argb("/tmp/test.png", test_data, 4, 4, 16))
      return 1;

   if (!rpng_load_image_argb(in_path, &data, &width, &height))
      return 2;

   fprintf(stderr, "Path: %s.\n", in_path);
   fprintf(stderr, "Got image: %u x %u.\n", width, height);

#if 0
   fprintf(stderr, "\nRPNG:\n");
   for (unsigned h = 0; h < height; h++)
   {
      unsigned w;
      for (w = 0; w < width; w++)
         fprintf(stderr, "[%08x] ", data[h * width + w]);
      fprintf(stderr, "\n");
   }
#endif

#ifdef HAVE_IMLIB2
   /* Validate with imlib2 as well. */
   img = imlib_load_image(in_path);
   if (!img)
      return 4;

   imlib_context_set_image(img);

   width      = imlib_image_get_width();
   height     = imlib_image_get_width();
   imlib_data = imlib_image_get_data_for_reading_only();

#if 0
   fprintf(stderr, "\nImlib:\n");
   for (unsigned h = 0; h < height; h++)
   {
      for (unsigned w = 0; w < width; w++)
         fprintf(stderr, "[%08x] ", imlib_data[h * width + w]);
      fprintf(stderr, "\n");
   }
#endif

   if (memcmp(imlib_data, data, width * height * sizeof(uint32_t)) != 0)
   {
      fprintf(stderr, "Imlib and RPNG differs!\n");
      return 5;
   }
   else
      fprintf(stderr, "Imlib and RPNG are equivalent!\n");

   imlib_free_image();
#endif
   free(data);

   return 0;
}