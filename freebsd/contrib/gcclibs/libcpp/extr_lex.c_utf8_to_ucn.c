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
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static size_t
utf8_to_ucn (unsigned char *buffer, const unsigned char *name)
{
  int j;
  int ucn_len = 0;
  int ucn_len_c;
  unsigned t;
  unsigned long utf32;
  
  /* Compute the length of the UTF-8 sequence.  */
  for (t = *name; t & 0x80; t <<= 1)
    ucn_len++;
  
  utf32 = *name & (0x7F >> ucn_len);
  for (ucn_len_c = 1; ucn_len_c < ucn_len; ucn_len_c++)
    {
      utf32 = (utf32 << 6) | (*++name & 0x3F);
      
      /* Ill-formed UTF-8.  */
      if ((*name & ~0x3F) != 0x80)
	abort ();
    }
  
  *buffer++ = '\\';
  *buffer++ = 'U';
  for (j = 7; j >= 0; j--)
    *buffer++ = "0123456789abcdef"[(utf32 >> (4 * j)) & 0xF];
  return ucn_len;
}