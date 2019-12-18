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
 int DIGIT_MAX ; 
 int UCHAR_MAX ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,int) ; 

void sort_pointers (size_t n, void **pointers, void **work)
{
  /* The type of a single digit.  This can be any unsigned integral
     type.  When changing this, DIGIT_MAX should be changed as 
     well.  */
  typedef unsigned char digit_t;

  /* The maximum value a single digit can have.  */
#define DIGIT_MAX (UCHAR_MAX + 1)

  /* The Ith entry is the number of elements in *POINTERSP that have I
     in the digit on which we are currently sorting.  */
  unsigned int count[DIGIT_MAX];
  /* Nonzero if we are running on a big-endian machine.  */
  int big_endian_p;
  size_t i;
  size_t j;

  /* The algorithm used here is radix sort which takes time linear in
     the number of elements in the array.  */

  /* The algorithm here depends on being able to swap the two arrays
     an even number of times.  */
  if ((sizeof (void *) / sizeof (digit_t)) % 2 != 0)
    abort ();

  /* Figure out the endianness of the machine.  */
  for (i = 0, j = 0; i < sizeof (size_t); ++i)
    {
      j *= (UCHAR_MAX + 1);
      j += i;
    }
  big_endian_p = (((char *)&j)[0] == 0);

  /* Move through the pointer values from least significant to most
     significant digits.  */
  for (i = 0; i < sizeof (void *) / sizeof (digit_t); ++i)
    {
      digit_t *digit;
      digit_t *bias;
      digit_t *top;
      unsigned int *countp;
      void **pointerp;

      /* The offset from the start of the pointer will depend on the
	 endianness of the machine.  */
      if (big_endian_p)
	j = sizeof (void *) / sizeof (digit_t) - i;
      else
	j = i;
	
      /* Now, perform a stable sort on this digit.  We use counting
	 sort.  */
      memset (count, 0, DIGIT_MAX * sizeof (unsigned int));

      /* Compute the address of the appropriate digit in the first and
	 one-past-the-end elements of the array.  On a little-endian
	 machine, the least-significant digit is closest to the front.  */
      bias = ((digit_t *) pointers) + j;
      top = ((digit_t *) (pointers + n)) + j;

      /* Count how many there are of each value.  At the end of this
	 loop, COUNT[K] will contain the number of pointers whose Ith
	 digit is K.  */
      for (digit = bias; 
	   digit < top; 
	   digit += sizeof (void *) / sizeof (digit_t))
	++count[*digit];

      /* Now, make COUNT[K] contain the number of pointers whose Ith
	 digit is less than or equal to K.  */
      for (countp = count + 1; countp < count + DIGIT_MAX; ++countp)
	*countp += countp[-1];

      /* Now, drop the pointers into their correct locations.  */
      for (pointerp = pointers + n - 1; pointerp >= pointers; --pointerp)
	work[--count[((digit_t *) pointerp)[j]]] = *pointerp;

      /* Swap WORK and POINTERS so that POINTERS contains the sorted
	 array.  */
      pointerp = pointers;
      pointers = work;
      work = pointerp;
    }
}