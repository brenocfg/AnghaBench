#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* opaque; void* zfree; void* zalloc; scalar_t__ avail_in; void* next_in; } ;
struct zlib {int state; int window_bits; int file_bits; int ok_bits; scalar_t__ rc; TYPE_1__ z; scalar_t__ cksum; scalar_t__ uncompressed_digits; scalar_t__ compressed_digits; int /*<<< orphan*/  rewrite_offset; int /*<<< orphan*/  global; int /*<<< orphan*/  file; struct chunk* chunk; struct IDAT* idat; } ;
struct chunk {int /*<<< orphan*/  global; int /*<<< orphan*/  file; } ;
struct IDAT {int dummy; } ;
typedef  int /*<<< orphan*/  png_uint_32 ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (struct zlib) ; 
 void* Z_NULL ; 
 scalar_t__ Z_OK ; 
 scalar_t__ inflateInit2 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlib_message (struct zlib*,int) ; 

__attribute__((used)) static int
zlib_init(struct zlib *zlib, struct IDAT *idat, struct chunk *chunk,
   int window_bits, png_uint_32 offset)
   /* Initialize a zlib_control; the result is true/false */
{
   CLEAR(*zlib);

   zlib->idat = idat;
   zlib->chunk = chunk;
   zlib->file = chunk->file;
   zlib->global = chunk->global;
   zlib->rewrite_offset = offset; /* never changed for this zlib */

   /* *_out does not need to be set: */
   zlib->z.next_in = Z_NULL;
   zlib->z.avail_in = 0;
   zlib->z.zalloc = Z_NULL;
   zlib->z.zfree = Z_NULL;
   zlib->z.opaque = Z_NULL;

   zlib->state = -1;
   zlib->window_bits = window_bits;

   zlib->compressed_digits = 0;
   zlib->uncompressed_digits = 0;

   /* These values are sticky across reset (in addition to the stuff in the
    * first block, which is actually constant.)
    */
   zlib->file_bits = 24;
   zlib->ok_bits = 16; /* unset */
   zlib->cksum = 0; /* set when a checksum error is detected */

   /* '0' means use the header; inflateInit2 should always succeed because it
    * does nothing apart from allocating the internal zstate.
    */
   zlib->rc = inflateInit2(&zlib->z, 0);
   if (zlib->rc != Z_OK)
   {
      zlib_message(zlib, 1/*unexpected*/);
      return 0;
   }

   else
   {
      zlib->state = 0; /* initialized */
      return 1;
   }
}