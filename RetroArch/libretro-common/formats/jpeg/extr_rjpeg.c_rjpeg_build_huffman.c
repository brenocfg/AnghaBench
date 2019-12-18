#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int* size; int* delta; int* code; int* maxcode; void** fast; } ;
typedef  TYPE_1__ rjpeg_huffman ;

/* Variables and functions */
 int FAST_BITS ; 
 int /*<<< orphan*/  memset (void**,int,int) ; 

__attribute__((used)) static int rjpeg_build_huffman(rjpeg_huffman *h, int *count)
{
   int i,j,k = 0,code;

   /* build size list for each symbol (from JPEG spec) */
   for (i = 0; i < 16; ++i)
      for (j = 0; j < count[i]; ++j)
         h->size[k++] = (uint8_t) (i+1);

   h->size[k] = 0;
   /* compute actual symbols (from jpeg spec) */
   code       = 0;
   k          = 0;

   for (j = 1; j <= 16; ++j)
   {
      /* compute delta to add to code to compute symbol id */
      h->delta[j] = k - code;
      if (h->size[k] == j)
      {
         while (h->size[k] == j)
            h->code[k++] = (uint16_t) (code++);

         /* Bad code lengths, corrupt JPEG? */
         if (code-1 >= (1 << j))
            return 0;
      }
      /* compute largest code + 1 for this size, preshifted as needed later */
      h->maxcode[j] = code << (16-j);
      code <<= 1;
   }
   h->maxcode[j] = 0xffffffff;

   /* build non-spec acceleration table; 255 is flag for not-accelerated */
   memset(h->fast, 255, 1 << FAST_BITS);
   for (i = 0; i < k; ++i)
   {
      int s = h->size[i];
      if (s <= FAST_BITS)
      {
         int c = h->code[i] << (FAST_BITS-s);
         int m = 1 << (FAST_BITS-s);
         for (j = 0; j < m; ++j)
            h->fast[c+j] = (uint8_t) i;
      }
   }
   return 1;
}