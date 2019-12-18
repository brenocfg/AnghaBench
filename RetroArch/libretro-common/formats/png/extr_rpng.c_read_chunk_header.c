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
typedef  int uint8_t ;
struct png_chunk {int* type; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  dword_be (int*) ; 

__attribute__((used)) static bool read_chunk_header(uint8_t *buf, uint8_t *buf_end, struct png_chunk *chunk)
{
   unsigned i;
   uint8_t dword[4];

   dword[0] = '\0';

   /* Check whether reading the header will overflow
    * the data buffer */
   if (buf_end - buf < 8)
      return false;

   for (i = 0; i < 4; i++)
      dword[i] = buf[i];

   chunk->size = dword_be(dword);

   /* Check whether chunk will overflow the data buffer */
   if (buf + 8 + chunk->size > buf_end)
      return false;

   for (i = 0; i < 4; i++)
   {
      uint8_t byte = buf[i + 4];

      /* All four bytes of the chunk type must be
       * ASCII letters (codes 65-90 and 97-122) */
      if ((byte < 65) || ((byte > 90) && (byte < 97)) || (byte > 122))
         return false;

      chunk->type[i] = byte;
   }

   return true;
}