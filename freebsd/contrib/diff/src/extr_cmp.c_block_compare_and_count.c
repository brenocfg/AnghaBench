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
typedef  char word ;
typedef  size_t off_t ;

/* Variables and functions */
 char CHAR_BIT ; 

__attribute__((used)) static size_t
block_compare_and_count (word const *p0, word const *p1, off_t *count)
{
  word l;		/* One word from first buffer. */
  word const *l0, *l1;	/* Pointers into each buffer. */
  char const *c0, *c1;	/* Pointers for finding exact address. */
  size_t cnt = 0;	/* Number of '\n' occurrences. */
  word nnnn;		/* Newline, sizeof (word) times.  */
  int i;

  nnnn = 0;
  for (i = 0; i < sizeof nnnn; i++)
    nnnn = (nnnn << CHAR_BIT) | '\n';

  /* Find the rough position of the first difference by reading words,
     not bytes.  */

  for (l0 = p0, l1 = p1;  (l = *l0) == *l1;  l0++, l1++)
    {
      l ^= nnnn;
      for (i = 0; i < sizeof l; i++)
	{
	  unsigned char uc = l;
	  cnt += ! uc;
	  l >>= CHAR_BIT;
	}
    }

  /* Find the exact differing position (endianness independent).  */

  for (c0 = (char const *) l0, c1 = (char const *) l1;
       *c0 == *c1;
       c0++, c1++)
    cnt += *c0 == '\n';

  *count += cnt;
  return c0 - (char const *) p0;
}