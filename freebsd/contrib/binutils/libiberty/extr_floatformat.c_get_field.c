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
typedef  enum floatformat_byteorders { ____Placeholder_floatformat_byteorders } floatformat_byteorders ;

/* Variables and functions */
 unsigned int FLOATFORMAT_CHAR_BIT ; 
 int floatformat_little ; 
 int min (unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned long
get_field (const unsigned char *data, enum floatformat_byteorders order,
           unsigned int total_len, unsigned int start, unsigned int len)
{
  unsigned long result = 0;
  unsigned int cur_byte;
  int lo_bit, hi_bit, cur_bitshift = 0;
  int nextbyte = (order == floatformat_little) ? 1 : -1;

  /* Start is in big-endian bit order!  Fix that first.  */
  start = total_len - (start + len);

  /* Start at the least significant part of the field.  */
  if (order == floatformat_little)
    cur_byte = start / FLOATFORMAT_CHAR_BIT;
  else
    cur_byte = (total_len - start - 1) / FLOATFORMAT_CHAR_BIT;

  lo_bit = start % FLOATFORMAT_CHAR_BIT;
  hi_bit = min (lo_bit + len, FLOATFORMAT_CHAR_BIT);
  
  do
    {
      unsigned int shifted = *(data + cur_byte) >> lo_bit;
      unsigned int bits = hi_bit - lo_bit;
      unsigned int mask = (1 << bits) - 1;
      result |= (shifted & mask) << cur_bitshift;
      len -= bits;
      cur_bitshift += bits;
      cur_byte += nextbyte;
      lo_bit = 0;
      hi_bit = min (len, FLOATFORMAT_CHAR_BIT);
    }
  while (len != 0);

  return result;
}