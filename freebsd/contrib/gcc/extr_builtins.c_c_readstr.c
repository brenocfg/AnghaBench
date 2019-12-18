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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 unsigned int BITS_PER_UNIT ; 
 scalar_t__ BYTES_BIG_ENDIAN ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 unsigned int GET_MODE_SIZE (int) ; 
 int HOST_BITS_PER_WIDE_INT ; 
 scalar_t__ MODE_INT ; 
 unsigned int UNITS_PER_WORD ; 
 scalar_t__ WORDS_BIG_ENDIAN ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  immed_double_const (int,int,int) ; 

__attribute__((used)) static rtx
c_readstr (const char *str, enum machine_mode mode)
{
  HOST_WIDE_INT c[2];
  HOST_WIDE_INT ch;
  unsigned int i, j;

  gcc_assert (GET_MODE_CLASS (mode) == MODE_INT);

  c[0] = 0;
  c[1] = 0;
  ch = 1;
  for (i = 0; i < GET_MODE_SIZE (mode); i++)
    {
      j = i;
      if (WORDS_BIG_ENDIAN)
	j = GET_MODE_SIZE (mode) - i - 1;
      if (BYTES_BIG_ENDIAN != WORDS_BIG_ENDIAN
	  && GET_MODE_SIZE (mode) > UNITS_PER_WORD)
	j = j + UNITS_PER_WORD - 2 * (j % UNITS_PER_WORD) - 1;
      j *= BITS_PER_UNIT;
      gcc_assert (j <= 2 * HOST_BITS_PER_WIDE_INT);

      if (ch)
	ch = (unsigned char) str[i];
      c[j / HOST_BITS_PER_WIDE_INT] |= ch << (j % HOST_BITS_PER_WIDE_INT);
    }
  return immed_double_const (c[0], c[1], mode);
}