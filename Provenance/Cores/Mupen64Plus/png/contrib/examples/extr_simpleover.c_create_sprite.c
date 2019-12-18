#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sprite {char const* name; int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * file; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  int /*<<< orphan*/ * png_uint_16p ;
struct TYPE_9__ {char* message; scalar_t__ colormap_entries; int /*<<< orphan*/  flags; void* format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/ * opaque; void* version; } ;
typedef  TYPE_1__ png_image ;

/* Variables and functions */
 void* PNG_FORMAT_LINEAR_RGB_ALPHA ; 
 int /*<<< orphan*/  PNG_IMAGE_FLAG_FAST ; 
 scalar_t__ PNG_IMAGE_SIZE (TYPE_1__) ; 
 void* PNG_IMAGE_VERSION ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ png_image_begin_read_from_file (TYPE_1__*,char const*) ; 
 scalar_t__ png_image_finish_read (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_image_free (TYPE_1__*) ; 
 scalar_t__ png_image_write_to_stdio (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprite_op (struct sprite*,int,int,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int sscanf (char const*,char*,int*,int*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tmpfile () ; 

__attribute__((used)) static int
create_sprite(struct sprite *sprite, int *argc, const char ***argv)
{
   /* Read the arguments and create this sprite. The sprite buffer has already
    * been allocated. This reads the input PNGs one by one in linear format,
    * composes them onto the sprite buffer (the code in the function above)
    * then saves the result, converting it on the fly to PNG RGBA 8-bit format.
    */
   while (*argc > 0)
   {
      char tombstone;
      int x = 0, y = 0;

      if ((*argv)[0][0] == '-' && (*argv)[0][1] == '-')
      {
         /* The only supported option is --at. */
         if (sscanf((*argv)[0], "--at=%d,%d%c", &x, &y, &tombstone) != 2)
            break; /* success; caller will parse this option */

         ++*argv, --*argc;
      }

      else
      {
         /* The argument has to be a file name */
         png_image image;

         image.version = PNG_IMAGE_VERSION;
         image.opaque = NULL;

         if (png_image_begin_read_from_file(&image, (*argv)[0]))
         {
            png_uint_16p buffer;

            image.format = PNG_FORMAT_LINEAR_RGB_ALPHA;

            buffer = malloc(PNG_IMAGE_SIZE(image));

            if (buffer != NULL)
            {
               if (png_image_finish_read(&image, NULL/*background*/, buffer,
                  0/*row_stride*/,
                  NULL/*colormap for PNG_FORMAT_FLAG_COLORMAP*/))
               {
                  /* This is the place where the Porter-Duff 'Over' operator
                   * needs to be done by this code.  In fact, any image
                   * processing required can be done here; the data is in
                   * the correct format (linear, 16-bit) and source and
                   * destination are in memory.
                   */
                  sprite_op(sprite, x, y, &image, buffer);
                  free(buffer);
                  ++*argv, --*argc;
                  /* And continue to the next argument */
                  continue;
               }

               else
               {
                  free(buffer);
                  fprintf(stderr, "simpleover: read %s: %s\n", (*argv)[0],
                      image.message);
               }
            }

            else
            {
               fprintf(stderr, "simpleover: out of memory: %lu bytes\n",
                  (unsigned long)PNG_IMAGE_SIZE(image));

               /* png_image_free must be called if we abort the Simplified API
                * read because of a problem detected in this code.  If problems
                * are detected in the Simplified API it cleans up itself.
                */
               png_image_free(&image);
            }
         }

         else
         {
            /* Failed to read the first argument: */
            fprintf(stderr, "simpleover: %s: %s\n", (*argv)[0], image.message);
         }

         return 0; /* failure */
      }
   }

   /* All the sprite operations have completed successfully. Save the RGBA
    * buffer as a PNG using the simplified write API.
    */
   sprite->file = tmpfile();

   if (sprite->file != NULL)
   {
      png_image save;

      memset(&save, 0, sizeof save);
      save.version = PNG_IMAGE_VERSION;
      save.opaque = NULL;
      save.width = sprite->width;
      save.height = sprite->height;
      save.format = PNG_FORMAT_LINEAR_RGB_ALPHA;
      save.flags = PNG_IMAGE_FLAG_FAST;
      save.colormap_entries = 0;

      if (png_image_write_to_stdio(&save, sprite->file, 1/*convert_to_8_bit*/,
          sprite->buffer, 0/*row_stride*/, NULL/*colormap*/))
      {
         /* Success; the buffer is no longer needed: */
         free(sprite->buffer);
         sprite->buffer = NULL;
         return 1; /* ok */
      }

      else
         fprintf(stderr, "simpleover: write sprite %s: %s\n", sprite->name,
            save.message);
   }

   else
      fprintf(stderr, "simpleover: sprite %s: could not allocate tmpfile: %s\n",
         sprite->name, strerror(errno));

   return 0; /* fail */
}