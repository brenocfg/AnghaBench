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
typedef  int valueT ;
typedef  int LITTLENUM_TYPE ;

/* Variables and functions */
 int LITTLENUM_MASK ; 
 scalar_t__ LITTLENUM_NUMBER_OF_BITS ; 

__attribute__((used)) static inline int
output_big_sleb128 (char *p, LITTLENUM_TYPE *bignum, int size)
{
  char *orig = p;
  valueT val = 0;
  int loaded = 0;
  unsigned byte;

  /* Strip leading sign extensions off the bignum.  */
  while (size > 1
	 && bignum[size - 1] == LITTLENUM_MASK
	 && bignum[size - 2] > LITTLENUM_MASK / 2)
    size--;

  do
    {
      /* OR in the next part of the littlenum.  */
      val |= (*bignum << loaded);
      loaded += LITTLENUM_NUMBER_OF_BITS;
      size--;
      bignum++;

      /* Add bytes until there are less than 7 bits left in VAL
	 or until every non-sign bit has been written.  */
      do
	{
	  byte = val & 0x7f;
	  loaded -= 7;
	  val >>= 7;
	  if (size > 0
	      || val != ((byte & 0x40) == 0 ? 0 : ((valueT) 1 << loaded) - 1))
	    byte |= 0x80;

	  if (orig)
	    *p = byte;
	  p++;
	}
      while ((byte & 0x80) != 0 && loaded >= 7);
    }
  while (size > 0);

  /* Mop up any left-over bits (of which there will be less than 7).  */
  if ((byte & 0x80) != 0)
    {
      /* Sign-extend VAL.  */
      if (val & (1 << (loaded - 1)))
	val |= ~0 << loaded;
      if (orig)
	*p = val & 0x7f;
      p++;
    }

  return p - orig;
}