#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sprite {int width; int height; char* name; int /*<<< orphan*/  file; } ;
typedef  TYPE_1__* png_imagep ;
struct TYPE_7__ {char const* message; int /*<<< orphan*/  format; int /*<<< orphan*/  version; } ;
typedef  TYPE_2__ png_image ;
typedef  scalar_t__ png_bytep ;
struct TYPE_6__ {unsigned int width; unsigned int height; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_FORMAT_RGB ; 
 int /*<<< orphan*/  PNG_IMAGE_VERSION ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 scalar_t__ png_image_begin_read_from_stdio (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ png_image_finish_read (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ ) ; 
 int sscanf (char const*,char*,int*,int*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
add_sprite(png_imagep output, png_bytep out_buf, struct sprite *sprite,
   int *argc, const char ***argv)
{
   /* Given a --add argument naming this sprite, perform the operations listed
    * in the following arguments.  The arguments are expected to have the form
    * (x,y), which is just an offset at which to add the sprite to the
    * output.
    */
   while (*argc > 0)
   {
      char tombstone;
      int x, y;

      if ((*argv)[0][0] == '-' && (*argv)[0][1] == '-')
         return 1; /* success */

      if (sscanf((*argv)[0], "%d,%d%c", &x, &y, &tombstone) == 2)
      {
         /* Now add the new image into the sprite data, but only if it
          * will fit.
          */
         if (x < 0 || y < 0 ||
             (unsigned)/*SAFE*/x >= output->width ||
             (unsigned)/*SAFE*/y >= output->height ||
             sprite->width > output->width-x ||
             sprite->height > output->height-y)
         {
            fprintf(stderr, "simpleover: sprite %s @ (%d,%d) outside image\n",
               sprite->name, x, y);
            /* Could just skip this, but for the moment it is an error */
            return 0; /* error */
         }

         else
         {
            /* Since we know the sprite fits we can just read it into the
             * output using the simplified API.
             */
            png_image in;

            in.version = PNG_IMAGE_VERSION;
            rewind(sprite->file);

            if (png_image_begin_read_from_stdio(&in, sprite->file))
            {
               in.format = PNG_FORMAT_RGB; /* force compose */

               if (png_image_finish_read(&in, NULL/*background*/,
                  out_buf + (y*output->width + x)*3/*RGB*/,
                  output->width*3/*row_stride*/,
                  NULL/*colormap for PNG_FORMAT_FLAG_COLORMAP*/))
               {
                  ++*argv, --*argc;
                  continue;
               }
            }

            /* The read failed: */
            fprintf(stderr, "simpleover: add sprite %s: %s\n", sprite->name,
                in.message);
            return 0; /* error */
         }
      }

      else
      {
         fprintf(stderr, "simpleover: --add='%s': invalid position %s\n",
               sprite->name, (*argv)[0]);
         return 0; /* error */
      }
   }

   return 1; /* ok */
}