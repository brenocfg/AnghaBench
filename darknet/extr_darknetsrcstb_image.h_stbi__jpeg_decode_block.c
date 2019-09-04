#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int stbi__uint16 ;
struct TYPE_8__ {int code_bits; int code_buffer; TYPE_1__* img_comp; } ;
typedef  TYPE_2__ stbi__jpeg ;
typedef  int stbi__int16 ;
typedef  int /*<<< orphan*/  stbi__huffman ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_7__ {int dc_pred; } ;

/* Variables and functions */
 int FAST_BITS ; 
 int /*<<< orphan*/  memset (short*,int /*<<< orphan*/ ,int) ; 
 int stbi__err (char*,char*) ; 
 int stbi__extend_receive (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stbi__grow_buffer_unsafe (TYPE_2__*) ; 
 unsigned int* stbi__jpeg_dezigzag ; 
 int stbi__jpeg_huff_decode (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stbi__jpeg_decode_block(stbi__jpeg *j, short data[64], stbi__huffman *hdc, stbi__huffman *hac, stbi__int16 *fac, int b, stbi__uint16 *dequant)
{
   int diff,dc,k;
   int t;

   if (j->code_bits < 16) stbi__grow_buffer_unsafe(j);
   t = stbi__jpeg_huff_decode(j, hdc);
   if (t < 0) return stbi__err("bad huffman code","Corrupt JPEG");

   // 0 all the ac values now so we can do it 32-bits at a time
   memset(data,0,64*sizeof(data[0]));

   diff = t ? stbi__extend_receive(j, t) : 0;
   dc = j->img_comp[b].dc_pred + diff;
   j->img_comp[b].dc_pred = dc;
   data[0] = (short) (dc * dequant[0]);

   // decode AC components, see JPEG spec
   k = 1;
   do {
      unsigned int zig;
      int c,r,s;
      if (j->code_bits < 16) stbi__grow_buffer_unsafe(j);
      c = (j->code_buffer >> (32 - FAST_BITS)) & ((1 << FAST_BITS)-1);
      r = fac[c];
      if (r) { // fast-AC path
         k += (r >> 4) & 15; // run
         s = r & 15; // combined length
         j->code_buffer <<= s;
         j->code_bits -= s;
         // decode into unzigzag'd location
         zig = stbi__jpeg_dezigzag[k++];
         data[zig] = (short) ((r >> 8) * dequant[zig]);
      } else {
         int rs = stbi__jpeg_huff_decode(j, hac);
         if (rs < 0) return stbi__err("bad huffman code","Corrupt JPEG");
         s = rs & 15;
         r = rs >> 4;
         if (s == 0) {
            if (rs != 0xf0) break; // end block
            k += 16;
         } else {
            k += r;
            // decode into unzigzag'd location
            zig = stbi__jpeg_dezigzag[k++];
            data[zig] = (short) (stbi__extend_receive(j,s) * dequant[zig]);
         }
      }
   } while (k < 64);
   return 1;
}