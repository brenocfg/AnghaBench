#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* message; int /*<<< orphan*/  format; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ png_image ;
typedef  int /*<<< orphan*/ * png_bytep ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_FORMAT_RGBA ; 
 scalar_t__ PNG_IMAGE_SIZE (TYPE_1__) ; 
 int /*<<< orphan*/  PNG_IMAGE_VERSION ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ png_image_begin_read_from_file (TYPE_1__*,char const*) ; 
 scalar_t__ png_image_finish_read (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_image_free (TYPE_1__*) ; 
 scalar_t__ png_image_write_to_file (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, const char **argv)
{
   int result = 1;

   if (argc == 3)
   {
      png_image image;

      /* Only the image structure version number needs to be set. */
      memset(&image, 0, sizeof image);
      image.version = PNG_IMAGE_VERSION;

      if (png_image_begin_read_from_file(&image, argv[1]))
      {
         png_bytep buffer;

         /* Change this to try different formats!  If you set a colormap format
          * then you must also supply a colormap below.
          */
         image.format = PNG_FORMAT_RGBA;

         buffer = malloc(PNG_IMAGE_SIZE(image));

         if (buffer != NULL)
         {
            if (png_image_finish_read(&image, NULL/*background*/, buffer,
               0/*row_stride*/, NULL/*colormap for PNG_FORMAT_FLAG_COLORMAP */))
            {
               if (png_image_write_to_file(&image, argv[2],
                  0/*convert_to_8bit*/, buffer, 0/*row_stride*/,
                  NULL/*colormap*/))
                  result = 0;

               else
                  fprintf(stderr, "pngtopng: write %s: %s\n", argv[2],
                      image.message);

               free(buffer);
            }

            else
            {
               fprintf(stderr, "pngtopng: read %s: %s\n", argv[1],
                   image.message);

               /* This is the only place where a 'free' is required; libpng does
                * the cleanup on error and success, but in this case we couldn't
                * complete the read because of running out of memory.
                */
               png_image_free(&image);
            }
         }

         else
            fprintf(stderr, "pngtopng: out of memory: %lu bytes\n",
               (unsigned long)PNG_IMAGE_SIZE(image));
      }

      else
         /* Failed to read the first argument: */
         fprintf(stderr, "pngtopng: %s: %s\n", argv[1], image.message);
   }

   else
      /* Wrong number of arguments */
      fprintf(stderr, "pngtopng: usage: pngtopng input-file output-file\n");

   return result;
}