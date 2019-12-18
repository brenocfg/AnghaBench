#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ png_size_t ;
struct TYPE_4__ {scalar_t__ bufsize; scalar_t__ allocsize; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  stride; int /*<<< orphan*/  image; } ;
typedef  TYPE_1__ Image ;

/* Variables and functions */
 int BUFFER_INIT8 ; 
 scalar_t__ PNG_IMAGE_BUFFER_SIZE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  freebuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  malloc (scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  png_bytep ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/ * voidcast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
allocbuffer(Image *image)
{
   png_size_t size = PNG_IMAGE_BUFFER_SIZE(image->image, image->stride);

   if (size+32 > image->bufsize)
   {
      freebuffer(image);
      image->buffer = voidcast(png_bytep, malloc(size+32));
      if (image->buffer == NULL)
      {
         fflush(stdout);
         fprintf(stderr,
            "simpletest: out of memory allocating %lu(+32) byte buffer\n",
            (unsigned long)size);
         exit(1);
      }
      image->bufsize = size+32;
   }

   memset(image->buffer, 95, image->bufsize);
   memset(image->buffer+16, BUFFER_INIT8, size);
   image->allocsize = size;
}