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
typedef  int ucs4_t ;

/* Variables and functions */
 scalar_t__ is_cjk_encoding (char const*) ; 
 int* nonspacing_table_data ; 
 int* nonspacing_table_ind ; 

int
uc_width (ucs4_t uc, const char *encoding)
{
  /* Test for non-spacing or control character.  */
  if ((uc >> 9) < 248)
    {
      int ind = nonspacing_table_ind[uc >> 9];
      if (ind >= 0)
        if ((nonspacing_table_data[64*ind + ((uc >> 3) & 63)] >> (uc & 7)) & 1)
          {
            if (uc > 0 && uc < 0xa0)
              return -1;
            else
              return 0;
          }
    }
  else if ((uc >> 9) == (0xe0000 >> 9))
    {
      if (uc >= 0xe0100)
        {
          if (uc <= 0xe01ef)
            return 0;
        }
      else
        {
          if (uc >= 0xe0020 ? uc <= 0xe007f : uc == 0xe0001)
            return 0;
        }
    }
  /* Test for double-width character.
   * Generated from "grep '^[^;]\{4,5\};[WF]' EastAsianWidth.txt"
   * and            "grep '^[^;]\{4,5\};[^WF]' EastAsianWidth.txt"
   */
  if (uc >= 0x1100
      && ((uc < 0x1160) /* Hangul Jamo */
          || (uc >= 0x2329 && uc < 0x232b) /* Angle Brackets */
          || (uc >= 0x2e80 && uc < 0xa4d0  /* CJK ... Yi */
              && !(uc == 0x303f) && !(uc >= 0x4dc0 && uc < 0x4e00))
          || (uc >= 0xac00 && uc < 0xd7a4) /* Hangul Syllables */
          || (uc >= 0xf900 && uc < 0xfb00) /* CJK Compatibility Ideographs */
          || (uc >= 0xfe10 && uc < 0xfe20) /* Presentation Forms for Vertical */
          || (uc >= 0xfe30 && uc < 0xfe70) /* CJK Compatibility Forms */
          || (uc >= 0xff00 && uc < 0xff61) /* Fullwidth Forms */
          || (uc >= 0xffe0 && uc < 0xffe7) /* Fullwidth Signs */
          || (uc >= 0x20000 && uc <= 0x2ffff) /* Supplementary Ideographic Plane */
          || (uc >= 0x30000 && uc <= 0x3ffff) /* Tertiary Ideographic Plane */
     )   )
    return 2;
  /* In ancient CJK encodings, Cyrillic and most other characters are
     double-width as well.  */
  if (uc >= 0x00A1 && uc < 0xFF61 && uc != 0x20A9
      && is_cjk_encoding (encoding))
    return 2;
  return 1;
}