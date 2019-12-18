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
 int CHECKSIZE ; 
 int MAXRECSIZE ; 
 int pmon_makeb64 (unsigned int,char*,int,unsigned int*) ; 
 int pmon_zeroset (int,char**,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static void
pmon_make_fastrec (char **outbuf, unsigned char *inbuf, int *inptr,
		   int inamount, int *recsize, unsigned int *csum,
		   unsigned int *zerofill)
{
  int count = 0;
  char *p = *outbuf;

  /* This is a simple check to ensure that our data will fit within
     the maximum allowable record size. Each record output is 4bytes
     in length. We must allow space for a pending zero fill command,
     the record, and a checksum record. */
  while ((*recsize < (MAXRECSIZE - CHECKSIZE)) && ((inamount - *inptr) > 0))
    {
      /* Process the binary data: */
      if ((inamount - *inptr) < 3)
	{
	  if (*zerofill != 0)
	    *recsize = pmon_zeroset (*recsize, &p, zerofill, csum);
	  sprintf (p, "/B");
	  count = pmon_makeb64 (inbuf[*inptr], &p[2], 12, csum);
	  p += (2 + count);
	  *recsize += (2 + count);
	  (*inptr)++;
	}
      else
	{
	  unsigned int value = ((inbuf[*inptr + 0] << 16) | (inbuf[*inptr + 1] << 8) | inbuf[*inptr + 2]);
	  /* Simple check for zero data. TODO: A better check would be
	     to check the last, and then the middle byte for being zero
	     (if the first byte is not). We could then check for
	     following runs of zeros, and if above a certain size it is
	     worth the 4 or 8 character hit of the byte insertions used
	     to pad to the start of the zeroes. NOTE: This also depends
	     on the alignment at the end of the zero run. */
	  if (value == 0x00000000)
	    {
	      (*zerofill)++;
	      if (*zerofill == 0xFFF)	/* 12bit counter */
		*recsize = pmon_zeroset (*recsize, &p, zerofill, csum);
	    }
	  else
	    {
	      if (*zerofill != 0)
		*recsize = pmon_zeroset (*recsize, &p, zerofill, csum);
	      count = pmon_makeb64 (value, p, 24, csum);
	      p += count;
	      *recsize += count;
	    }
	  *inptr += 3;
	}
    }

  *outbuf = p;
  return;
}