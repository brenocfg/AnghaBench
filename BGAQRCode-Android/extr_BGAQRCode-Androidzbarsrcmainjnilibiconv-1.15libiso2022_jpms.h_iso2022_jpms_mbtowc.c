#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char ucs4_t ;
typedef  int state_t ;
typedef  TYPE_1__* conv_t ;
struct TYPE_9__ {int istate; } ;

/* Variables and functions */
 unsigned char ESC ; 
 int RET_ILSEQ ; 
 int RET_SHIFT_ILSEQ (int) ; 
 int RET_TOOFEW (int) ; 
 unsigned char SI ; 
 unsigned char SO ; 
#define  STATE_ASCII 132 
#define  STATE_JISX0201KATAKANA 131 
#define  STATE_JISX0201ROMAN 130 
#define  STATE_JISX0208MS 129 
#define  STATE_JISX0212MS 128 
 int /*<<< orphan*/  abort () ; 
 int ascii_mbtowc (TYPE_1__*,unsigned char*,unsigned char const*,int) ; 
 int cp50221_0208_ext_mbtowc (TYPE_1__*,unsigned char*,unsigned char*,int) ; 
 int cp50221_0212_ext_mbtowc (TYPE_1__*,unsigned char*,unsigned char*,int) ; 
 unsigned short* cp932ext_2uni_pageed ; 
 int jisx0201_mbtowc (TYPE_1__*,unsigned char*,unsigned char const*,int) ; 
 int jisx0208_mbtowc (TYPE_1__*,unsigned char*,unsigned char const*,int) ; 
 int jisx0212_mbtowc (TYPE_1__*,unsigned char*,unsigned char const*,int) ; 

__attribute__((used)) static int
iso2022_jpms_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, size_t n)
{
  state_t state = conv->istate;
  int count = 0;
  unsigned char c;
  for (;;) {
    c = *s;
    if (c == ESC) {
      if (n < count+3)
        goto none;
      if (s[1] == '(') {
        if (s[2] == 'B') {
          state = STATE_ASCII;
          s += 3; count += 3;
          if (n < count+1)
            goto none;
          continue;
        }
        if (s[2] == 'I') {
          state = STATE_JISX0201KATAKANA;
          s += 3; count += 3;
          if (n < count+1)
            goto none;
          continue;
        }
        if (s[2] == 'J') {
          state = STATE_JISX0201ROMAN;
          s += 3; count += 3;
          if (n < count+1)
            goto none;
          continue;
        }
        goto ilseq;
      }
      if (s[1] == '$') {
        if (s[2] == '@' || s[2] == 'B') {
          /* We don't distinguish JIS X 0208-1978 and JIS X 0208-1983. */
          state = STATE_JISX0208MS;
          s += 3; count += 3;
          if (n < count+1)
            goto none;
          continue;
        }
        if (s[2] == '(') {
          if (n < count+4)
            goto none;
          if (s[3] == 'D') {
            state = STATE_JISX0212MS;
            s += 4; count += 4;
            if (n < count+1)
              goto none;
            continue;
          }
        }
        goto ilseq;
      }
      goto ilseq;
    }
    if (c == SO) {
      if (state == STATE_JISX0201ROMAN)
        state = STATE_JISX0201KATAKANA;
      s += 1; count += 1;
      if (n < count+1)
        goto none;
      continue;
    }
    if (c == SI) {
      if (state == STATE_JISX0201KATAKANA)
        state = STATE_JISX0201ROMAN;
      s += 1; count += 1;
      if (n < count+1)
        goto none;
      continue;
    }
    break;
  }
  switch (state) {
    case STATE_ASCII:
      if (c < 0x80) {
        int ret = ascii_mbtowc(conv,pwc,s,1);
        if (ret == RET_ILSEQ)
          goto ilseq;
        if (ret != 1) abort();
        conv->istate = state;
        return count+1;
      } else
        goto ilseq;
    case STATE_JISX0201ROMAN:
      if (c < 0x80) {
        int ret = jisx0201_mbtowc(conv,pwc,s,1);
        if (ret == RET_ILSEQ)
          goto ilseq;
        if (ret != 1) abort();
        conv->istate = state;
        return count+1;
      } else
        goto ilseq;
    case STATE_JISX0201KATAKANA:
      if (c < 0x80) {
        unsigned char buf = c+0x80;
        int ret = jisx0201_mbtowc(conv,pwc,&buf,1);
        if (ret == RET_ILSEQ)
          goto ilseq;
        if (ret != 1) abort();
        conv->istate = state;
        return count+1;
      } else
        goto ilseq;
    case STATE_JISX0208MS:
      if (n < count+2)
        goto none;
      if (s[0] < 0x80 && s[1] < 0x80) {
        int ret;
        if (s[0] < 0x75) {
          if (s[0] == 0x2d) {
            /* Extension of JIS X 0208.  */
            if (s[1] >= 0x21 && s[1] <= 0x79) {
              unsigned char i = (s[1] - 0x21) + 1;
              ret = cp50221_0208_ext_mbtowc(conv,pwc,&i,1);
              if (ret == 1)
                ret = 2;
            } else
              ret = RET_ILSEQ;
          } else {
            /* JIS X 0208.  */
            ret = jisx0208_mbtowc(conv,pwc,s,2);
          }
        } else {
          /* Extension of JIS X 0208.
             0x{75..7E}{21..8E} maps to U+E000..U+E3AB.
             But some rows maps to characters present in CP932.  */
          if (s[0] <= 0x7e && (s[1] >= 0x21 && s[1] <= 0x7e)) {
            unsigned short wc = 0xfffd;
            if (s[0] >= 0x79 && s[0] <= 0x7c)
              wc = cp932ext_2uni_pageed[(s[0] - 0x79) * 94 + (s[1] - 0x21)];
            if (wc == 0xfffd)
              wc = (s[0] - 0x75) * 94 + (s[1] - 0x21) + 0xe000;
            *pwc = wc;
            ret = 2;
          } else
            ret = RET_ILSEQ;
        }
        if (ret == RET_ILSEQ)
          goto ilseq;
        if (ret != 2) abort();
        conv->istate = state;
        return count+2;
      } else
        goto ilseq;
    case STATE_JISX0212MS:
      if (n < count+2)
        goto none;
      if (s[0] < 0x80 && s[1] < 0x80) {
        int ret;
        if (s[0] < 0x73) {
          /* JIS X 0212.  */
          ret = jisx0212_mbtowc(conv,pwc,s,2);
        } else {
          if (s[0] < 0x75) {
            /* Extension of JIS X 0212.  */
            if (s[1] >= 0x21 && s[1] <= 0x7e) {
              unsigned char i = (s[0] - 0x73) * 94 + (s[1] - 0x21) + 1;
              ret = cp50221_0212_ext_mbtowc(conv,pwc,&i,1);
              if (ret == 1)
                ret = 2;
            } else
              ret = RET_ILSEQ;
          } else {
            /* Extension of JIS X 0208.
               0x{75..7E}{21..8E} maps to U+E3AC..U+E757.  */
            if (s[0] <= 0x7e && (s[1] >= 0x21 && s[1] <= 0x7e)) {
              *pwc = (s[0] - 0x75) * 94 + (s[1] - 0x21) + 0xe3ac;
              ret = 2;
            } else
              ret = RET_ILSEQ;
          }
        }
        if (ret == RET_ILSEQ)
          goto ilseq;
        if (ret != 2) abort();
        conv->istate = state;
        return count+2;
      } else
        goto ilseq;
    default: abort();
  }

none:
  conv->istate = state;
  return RET_TOOFEW(count);

ilseq:
  conv->istate = state;
  return RET_SHIFT_ILSEQ(count);
}