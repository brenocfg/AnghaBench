#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int leader; unsigned int low; unsigned int high; scalar_t__ exponent; int /*<<< orphan*/  sign; } ;
typedef  int /*<<< orphan*/  LITTLENUM_TYPE ;
typedef  TYPE_1__ FLONUM_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 int /*<<< orphan*/  memset (char*,char,unsigned int) ; 

void
flonum_copy (FLONUM_TYPE *in, FLONUM_TYPE *out)
{
  unsigned int in_length;	/* 0 origin */
  unsigned int out_length;	/* 0 origin */

  out->sign = in->sign;
  in_length = in->leader - in->low;

  if (in->leader < in->low)
    {
      out->leader = out->low - 1;	/* 0.0 case */
    }
  else
    {
      out_length = out->high - out->low;
      /* Assume no GAPS in packing of littlenums.
	 I.e. sizeof(array) == sizeof(element) * number_of_elements.  */
      if (in_length <= out_length)
	{
	  {
	    /* For defensive programming, zero any high-order
	       littlenums we don't need.  This is destroying evidence
	       and wasting time, so why bother???  */
	    if (in_length < out_length)
	      {
		memset ((char *) (out->low + in_length + 1), '\0',
			out_length - in_length);
	      }
	  }
	  memcpy ((void *) (out->low), (void *) (in->low),
		  ((in_length + 1) * sizeof (LITTLENUM_TYPE)));
	  out->exponent = in->exponent;
	  out->leader = in->leader - in->low + out->low;
	}
      else
	{
	  int shorten;		/* 1-origin. Number of littlenums we drop.  */

	  shorten = in_length - out_length;
	  /* Assume out_length >= 0 ! */
	  memcpy ((void *) (out->low), (void *) (in->low + shorten),
		  ((out_length + 1) * sizeof (LITTLENUM_TYPE)));
	  out->leader = out->high;
	  out->exponent = in->exponent + shorten;
	}
    }				/* if any significant bits */
}