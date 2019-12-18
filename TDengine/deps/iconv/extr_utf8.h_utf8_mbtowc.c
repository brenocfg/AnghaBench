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
typedef  int /*<<< orphan*/  conv_t ;

/* Variables and functions */
 int RET_ILSEQ ; 
 int RET_TOOFEW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
utf8_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  unsigned char c = s[0];

  if (c < 0x80) {
    *pwc = c;
    return 1;
  } else if (c < 0xc2) {
    return RET_ILSEQ;
  } else if (c < 0xe0) {
    if (n < 2)
      return RET_TOOFEW(0);
    if (!((s[1] ^ 0x80) < 0x40))
      return RET_ILSEQ;
    *pwc = ((ucs4_t) (c & 0x1f) << 6)
           | (ucs4_t) (s[1] ^ 0x80);
    return 2;
  } else if (c < 0xf0) {
    if (n < 3)
      return RET_TOOFEW(0);
    if (!((s[1] ^ 0x80) < 0x40 && (s[2] ^ 0x80) < 0x40
          && (c >= 0xe1 || s[1] >= 0xa0)))
      return RET_ILSEQ;
    *pwc = ((ucs4_t) (c & 0x0f) << 12)
           | ((ucs4_t) (s[1] ^ 0x80) << 6)
           | (ucs4_t) (s[2] ^ 0x80);
    return 3;
  } else if (c < 0xf8 && sizeof(ucs4_t)*8 >= 32) {
    if (n < 4)
      return RET_TOOFEW(0);
    if (!((s[1] ^ 0x80) < 0x40 && (s[2] ^ 0x80) < 0x40
          && (s[3] ^ 0x80) < 0x40
          && (c >= 0xf1 || s[1] >= 0x90)))
      return RET_ILSEQ;
    *pwc = ((ucs4_t) (c & 0x07) << 18)
           | ((ucs4_t) (s[1] ^ 0x80) << 12)
           | ((ucs4_t) (s[2] ^ 0x80) << 6)
           | (ucs4_t) (s[3] ^ 0x80);
    return 4;
  } else if (c < 0xfc && sizeof(ucs4_t)*8 >= 32) {
    if (n < 5)
      return RET_TOOFEW(0);
    if (!((s[1] ^ 0x80) < 0x40 && (s[2] ^ 0x80) < 0x40
          && (s[3] ^ 0x80) < 0x40 && (s[4] ^ 0x80) < 0x40
          && (c >= 0xf9 || s[1] >= 0x88)))
      return RET_ILSEQ;
    *pwc = ((ucs4_t) (c & 0x03) << 24)
           | ((ucs4_t) (s[1] ^ 0x80) << 18)
           | ((ucs4_t) (s[2] ^ 0x80) << 12)
           | ((ucs4_t) (s[3] ^ 0x80) << 6)
           | (ucs4_t) (s[4] ^ 0x80);
    return 5;
  } else if (c < 0xfe && sizeof(ucs4_t)*8 >= 32) {
    if (n < 6)
      return RET_TOOFEW(0);
    if (!((s[1] ^ 0x80) < 0x40 && (s[2] ^ 0x80) < 0x40
          && (s[3] ^ 0x80) < 0x40 && (s[4] ^ 0x80) < 0x40
          && (s[5] ^ 0x80) < 0x40
          && (c >= 0xfd || s[1] >= 0x84)))
      return RET_ILSEQ;
    *pwc = ((ucs4_t) (c & 0x01) << 30)
           | ((ucs4_t) (s[1] ^ 0x80) << 24)
           | ((ucs4_t) (s[2] ^ 0x80) << 18)
           | ((ucs4_t) (s[3] ^ 0x80) << 12)
           | ((ucs4_t) (s[4] ^ 0x80) << 6)
           | (ucs4_t) (s[5] ^ 0x80);
    return 6;
  } else
    return RET_ILSEQ;
}