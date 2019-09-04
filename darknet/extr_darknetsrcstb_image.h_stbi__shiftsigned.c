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

/* Variables and functions */
 int /*<<< orphan*/  STBI_ASSERT (int) ; 

__attribute__((used)) static int stbi__shiftsigned(int v, int shift, int bits)
{
   static unsigned int mul_table[9] = {
      0,
      0xff/*0b11111111*/, 0x55/*0b01010101*/, 0x49/*0b01001001*/, 0x11/*0b00010001*/,
      0x21/*0b00100001*/, 0x41/*0b01000001*/, 0x81/*0b10000001*/, 0x01/*0b00000001*/,
   };
   static unsigned int shift_table[9] = {
      0, 0,0,1,0,2,4,6,0,
   };
   if (shift < 0)
      v <<= -shift;
   else
      v >>= shift;
   STBI_ASSERT(v >= 0 && v < 256);
   v >>= (8-bits);
   STBI_ASSERT(bits >= 0 && bits <= 8);
   return (int) ((unsigned) v * mul_table[bits]) >> shift_table[bits];
}