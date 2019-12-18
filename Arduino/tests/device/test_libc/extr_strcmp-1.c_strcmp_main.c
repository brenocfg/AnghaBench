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
 int BUFF_SIZE ; 
 unsigned int MAX_BLOCK_SIZE ; 
 unsigned int MAX_DIFF ; 
 unsigned int MAX_LEN ; 
 unsigned int MAX_OFFSET ; 
 int MAX_ZEROS ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  delay (int /*<<< orphan*/ ) ; 
 scalar_t__ errors ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  print_error (char*,int,...) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rand_seed ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int strcmp (char*,char*) ; 
 int /*<<< orphan*/  testname ; 

void strcmp_main(void)
{
  /* Allocate buffers to read and write from.  */
  char src[BUFF_SIZE], dest[BUFF_SIZE];

  /* Fill the source buffer with non-null values, reproducable random data.  */
  srand (rand_seed);
  int i, j, zeros;
  unsigned sa;
  unsigned da;
  unsigned n, m, len;
  char *p;
  int ret;

  /* Make calls to strcmp with block sizes ranging between 1 and
     MAX_BLOCK_SIZE bytes, aligned and misaligned source and destination.  */
  for (sa = 0; sa <= MAX_OFFSET; sa++)
    for (da = 0; da <= MAX_OFFSET; da++)
      for (n = 1; n <= MAX_BLOCK_SIZE; n++)
	{
	for (m = 1;  m < n + MAX_DIFF; m++)
	  for (len = 0; len < MAX_LEN; len++)
	    for  (zeros = 1; zeros < MAX_ZEROS; zeros++)
	    {
	      if (n - m > MAX_DIFF)
		continue;
	      /* Make a copy of the source.  */
	      for (i = 0; i < BUFF_SIZE; i++)
		{
		  src[i] = 'A' + (i % 26);
		  dest[i] = src[i];
		}
   delay(0);
	      memcpy (dest + da, src + sa, n);

	      /* Make src 0-terminated.  */
	      p = src + sa + n - 1;
	      for (i = 0; i < zeros; i++)
		{
		  *p++ = '\0';
		}

	      /* Modify dest.  */
	      p = dest + da + m - 1;
	      for (j = 0; j < (int)len; j++)
		*p++ = 'x';
	      /* Make dest 0-terminated.  */
	      *p = '\0';

	      ret = strcmp (src + sa, dest + da);

	      /* Check return value.  */
	      if (n == m)
		{
		  if (len == 0)
		    {
		      if (ret != 0)
			{
			print_error ("\nFailed: after %s of %u bytes "
				     "with src_align %u and dst_align %u, "
				     "dest after %d bytes is modified for %d bytes, "
				     "return value is %d, expected 0.\n",
				     testname, n, sa, da, m, len, ret);
			}
		    }
		  else
		    {
		      if (ret >= 0)
			print_error ("\nFailed: after %s of %u bytes "
				     "with src_align %u and dst_align %u, "
				     "dest after %d bytes is modified for %d bytes, "
				     "return value is %d, expected negative.\n",
				     testname, n, sa, da, m, len, ret);
		    }
		}
	      else if (m > n)
		{
		  if (ret >= 0)
		    {
		      print_error ("\nFailed: after %s of %u bytes "
				   "with src_align %u and dst_align %u, "
				   "dest after %d bytes is modified for %d bytes, "
				   "return value is %d, expected negative.\n",
				   testname, n, sa, da, m, len, ret);
		    }
		}
	      else  /* m < n */
		{
		  if (len == 0)
		    {
		      if (ret <= 0)
			print_error ("\nFailed: after %s of %u bytes "
				     "with src_align %u and dst_align %u, "
				     "dest after %d bytes is modified for %d bytes, "
				     "return value is %d, expected positive.\n",
				     testname, n, sa, da, m, len, ret);
		    }
		  else
		    {
		      if (ret >= 0)
			print_error ("\nFailed: after %s of %u bytes "
				     "with src_align %u and dst_align %u, "
				     "dest after %d bytes is modified for %d bytes, "
				     "return value is %d, expected negative.\n",
				     testname, n, sa, da, m, len, ret);
		    }
		}
	    }
	}

  /* Check some corner cases.  */
  src[1] = 'A';
  dest[1] = 'A';
  src[2] = 'B';
  dest[2] = 'B';
  src[3] = 'C';
  dest[3] = 'C';
  src[4] = '\0';
  dest[4] = '\0';

  src[0] = 0xc1;
  dest[0] = 0x41;
  ret = strcmp (src, dest);
  if (ret <= 0)
    print_error ("\nFailed: expected positive, return %d\n", ret);

  src[0] = 0x01;
  dest[0] = 0x82;
  ret = strcmp (src, dest);
  if (ret >= 0)
    print_error ("\nFailed: expected negative, return %d\n", ret);

  dest[0] = src[0] = 'D';
  src[3] = 0xc1;
  dest[3] = 0x41;
  ret = strcmp (src, dest);
  if (ret <= 0)
    print_error ("\nFailed: expected positive, return %d\n", ret);

  src[3] = 0x01;
  dest[3] = 0x82;
  ret = strcmp (src, dest);
  if (ret >= 0)
    print_error ("\nFailed: expected negative, return %d\n", ret);

  //printf ("\n");
  if (errors != 0)
    {
      printf ("ERROR. FAILED.\n");
      abort ();
    }
  //exit (0);
  printf("ok\n");
}