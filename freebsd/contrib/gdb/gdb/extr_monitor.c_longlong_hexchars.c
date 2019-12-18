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
 void** hexlate ; 
 int /*<<< orphan*/  longlongendswap (unsigned char*) ; 

__attribute__((used)) static char *
longlong_hexchars (unsigned long long value,
		   char *outbuff)
{
  if (value == 0)
    {
      *outbuff++ = '0';
      return outbuff;
    }
  else
    {
      static unsigned char disbuf[8];	/* disassembly buffer */
      unsigned char *scan, *limit;	/* loop controls */
      unsigned char c, nib;
      int leadzero = 1;
      scan = disbuf;
      limit = scan + 8;
      {
	unsigned long long *dp;
	dp = (unsigned long long *) scan;
	*dp = value;
      }
      longlongendswap (disbuf);	/* FIXME: ONly on big endian hosts */
      while (scan < limit)
	{
	  c = *scan++;		/* a byte of our long long value */
	  if (leadzero)
	    {
	      if (c == 0)
		continue;
	      else
		leadzero = 0;	/* henceforth we print even zeroes */
	    }
	  nib = c >> 4;		/* high nibble bits */
	  *outbuff++ = hexlate[nib];
	  nib = c & 0x0f;	/* low nibble bits */
	  *outbuff++ = hexlate[nib];
	}
      return outbuff;
    }
}