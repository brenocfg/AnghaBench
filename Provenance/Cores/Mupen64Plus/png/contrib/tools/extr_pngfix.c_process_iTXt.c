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
struct file {int /*<<< orphan*/ * idat; struct chunk* chunk; } ;
struct chunk {int chunk_length; } ;
typedef  int png_uint_32 ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_ERROR_CODE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  log_error (struct file*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ reread_byte (struct file*) ; 
 int /*<<< orphan*/  setpos (struct chunk*) ; 
 int zlib_check (struct file*,int) ; 

__attribute__((used)) static int
process_iTXt(struct file *file)
{
   /* Like zTXt but more fields. */
   struct chunk *chunk = file->chunk;
   png_uint_32 length;
   png_uint_32 index = 0;

   assert(chunk != NULL && file->idat == NULL);
   length = chunk->chunk_length;
   setpos(chunk);

   while (length >= 5)
   {
      --length;
      ++index;
      if (reread_byte(file) == 0) /* keyword null terminator */
      {
         --length;
         ++index;
         if (reread_byte(file) == 0) /* uncompressed text */
            return 1; /* nothing to check */

         --length;
         ++index;
         (void)reread_byte(file); /* compression method */

         /* Skip the language tag (null terminated). */
         while (length >= 9)
         {
            --length;
            ++index;
            if (reread_byte(file) == 0) /* terminator */
            {
               /* Skip the translated keyword */
               while (length >= 8)
               {
                  --length;
                  ++index;
                  if (reread_byte(file) == 0) /* terminator */
                     return zlib_check(file, index);
               }
            }
         }

         /* Ran out of bytes in the compressed case. */
         break;
      }
   }

   log_error(file, INVALID_ERROR_CODE, "iTXt chunk length");

   return 0; /* skip */
}