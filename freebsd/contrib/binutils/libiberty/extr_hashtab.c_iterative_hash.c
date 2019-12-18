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
typedef  int hashval_t ;
typedef  scalar_t__ PTR ;

/* Variables and functions */
 int /*<<< orphan*/  mix (int,int,int) ; 

hashval_t
iterative_hash (const PTR k_in /* the key */,
                register size_t  length /* the length of the key */,
                register hashval_t initval /* the previous hash, or
                                              an arbitrary value */)
{
  register const unsigned char *k = (const unsigned char *)k_in;
  register hashval_t a,b,c,len;

  /* Set up the internal state */
  len = length;
  a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
  c = initval;           /* the previous hash value */

  /*---------------------------------------- handle most of the key */
#ifndef WORDS_BIGENDIAN
  /* On a little-endian machine, if the data is 4-byte aligned we can hash
     by word for better speed.  This gives nondeterministic results on
     big-endian machines.  */
  if (sizeof (hashval_t) == 4 && (((size_t)k)&3) == 0)
    while (len >= 12)    /* aligned */
      {
	a += *(hashval_t *)(k+0);
	b += *(hashval_t *)(k+4);
	c += *(hashval_t *)(k+8);
	mix(a,b,c);
	k += 12; len -= 12;
      }
  else /* unaligned */
#endif
    while (len >= 12)
      {
	a += (k[0] +((hashval_t)k[1]<<8) +((hashval_t)k[2]<<16) +((hashval_t)k[3]<<24));
	b += (k[4] +((hashval_t)k[5]<<8) +((hashval_t)k[6]<<16) +((hashval_t)k[7]<<24));
	c += (k[8] +((hashval_t)k[9]<<8) +((hashval_t)k[10]<<16)+((hashval_t)k[11]<<24));
	mix(a,b,c);
	k += 12; len -= 12;
      }

  /*------------------------------------- handle the last 11 bytes */
  c += length;
  switch(len)              /* all the case statements fall through */
    {
    case 11: c+=((hashval_t)k[10]<<24);
    case 10: c+=((hashval_t)k[9]<<16);
    case 9 : c+=((hashval_t)k[8]<<8);
      /* the first byte of c is reserved for the length */
    case 8 : b+=((hashval_t)k[7]<<24);
    case 7 : b+=((hashval_t)k[6]<<16);
    case 6 : b+=((hashval_t)k[5]<<8);
    case 5 : b+=k[4];
    case 4 : a+=((hashval_t)k[3]<<24);
    case 3 : a+=((hashval_t)k[2]<<16);
    case 2 : a+=((hashval_t)k[1]<<8);
    case 1 : a+=k[0];
      /* case 0: nothing left to add */
    }
  mix(a,b,c);
  /*-------------------------------------------- report the result */
  return c;
}