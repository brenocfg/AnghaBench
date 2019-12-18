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
struct _getopt_data {int __first_nonopt; int __last_nonopt; int optind; scalar_t__ __nonoption_flags_len; int __nonoption_flags_max_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAP_FLAGS (int,int) ; 
 char* __getopt_nonoption_flags ; 
 int /*<<< orphan*/  __mempcpy (char*,char*,scalar_t__) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,char,int) ; 

__attribute__((used)) static void
exchange (char **argv, struct _getopt_data *d)
{
  int bottom = d->__first_nonopt;
  int middle = d->__last_nonopt;
  int top = d->optind;
  char *tem;

  /* Exchange the shorter segment with the far end of the longer segment.
     That puts the shorter segment into the right place.
     It leaves the longer segment in the right place overall,
     but it consists of two parts that need to be swapped next.  */

#if defined _LIBC && defined USE_NONOPTION_FLAGS
  /* First make sure the handling of the `__getopt_nonoption_flags'
     string can work normally.  Our top argument must be in the range
     of the string.  */
  if (d->__nonoption_flags_len > 0 && top >= d->__nonoption_flags_max_len)
    {
      /* We must extend the array.  The user plays games with us and
	 presents new arguments.  */
      char *new_str = malloc (top + 1);
      if (new_str == NULL)
	d->__nonoption_flags_len = d->__nonoption_flags_max_len = 0;
      else
	{
	  memset (__mempcpy (new_str, __getopt_nonoption_flags,
			     d->__nonoption_flags_max_len),
		  '\0', top + 1 - d->__nonoption_flags_max_len);
	  d->__nonoption_flags_max_len = top + 1;
	  __getopt_nonoption_flags = new_str;
	}
    }
#endif

  while (top > middle && middle > bottom)
    {
      if (top - middle > middle - bottom)
	{
	  /* Bottom segment is the short one.  */
	  int len = middle - bottom;
	  register int i;

	  /* Swap it with the top part of the top segment.  */
	  for (i = 0; i < len; i++)
	    {
	      tem = argv[bottom + i];
	      argv[bottom + i] = argv[top - (middle - bottom) + i];
	      argv[top - (middle - bottom) + i] = tem;
	      SWAP_FLAGS (bottom + i, top - (middle - bottom) + i);
	    }
	  /* Exclude the moved bottom segment from further swapping.  */
	  top -= len;
	}
      else
	{
	  /* Top segment is the short one.  */
	  int len = top - middle;
	  register int i;

	  /* Swap it with the bottom part of the bottom segment.  */
	  for (i = 0; i < len; i++)
	    {
	      tem = argv[bottom + i];
	      argv[bottom + i] = argv[middle + i];
	      argv[middle + i] = tem;
	      SWAP_FLAGS (bottom + i, middle + i);
	    }
	  /* Exclude the moved top segment from further swapping.  */
	  bottom += len;
	}
    }

  /* Update records for the slots the non-options now occupy.  */

  d->__first_nonopt += (d->optind - d->__last_nonopt);
  d->__last_nonopt = d->optind;
}