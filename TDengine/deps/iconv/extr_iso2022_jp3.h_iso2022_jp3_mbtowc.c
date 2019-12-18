#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ucs4_t ;
typedef  int state_t ;
typedef  TYPE_1__* conv_t ;
struct TYPE_6__ {int istate; } ;

/* Variables and functions */
 unsigned char ESC ; 
 int RET_ILSEQ ; 
 int RET_SHIFT_ILSEQ (int) ; 
 int RET_TOOFEW (int) ; 
#define  STATE_ASCII 133 
#define  STATE_JISX0201KATAKANA 132 
#define  STATE_JISX0201ROMAN 131 
#define  STATE_JISX0208 130 
#define  STATE_JISX02131 129 
#define  STATE_JISX02132 128 
 int /*<<< orphan*/  abort () ; 
 int ascii_mbtowc (TYPE_1__*,int*,unsigned char const*,int) ; 
 int jisx0201_mbtowc (TYPE_1__*,int*,unsigned char const*,int) ; 
 int jisx0208_mbtowc (TYPE_1__*,int*,unsigned char const*,int) ; 
 int jisx0213_to_ucs4 (int,unsigned char const) ; 
 int** jisx0213_to_ucs_combining ; 

__attribute__((used)) static int
iso2022_jp3_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  ucs4_t last_wc = conv->istate >> 3;
  if (last_wc) {
    /* Output the buffered character. */
    conv->istate &= 7;
    *pwc = last_wc;
    return 0; /* Don't advance the input pointer. */
  } else {
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
          if (s[2] == 'J') {
            state = STATE_JISX0201ROMAN;
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
          goto ilseq;
        }
        if (s[1] == '$') {
          if (s[2] == '@' || s[2] == 'B') {
            /* We don't distinguish JIS X 0208-1978 and JIS X 0208-1983. */
            state = STATE_JISX0208;
            s += 3; count += 3;
            if (n < count+1)
              goto none;
            continue;
          }
          if (s[2] == '(') {
            if (n < count+4)
              goto none;
            if (s[3] == 'O' || s[3] == 'Q') {
              state = STATE_JISX02131;
              s += 4; count += 4;
              if (n < count+1)
                goto none;
              continue;
            }
            if (s[3] == 'P') {
              state = STATE_JISX02132;
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
      case STATE_JISX0208:
        if (n < count+2)
          goto none;
        if (s[0] < 0x80 && s[1] < 0x80) {
          int ret = jisx0208_mbtowc(conv,pwc,s,2);
          if (ret == RET_ILSEQ)
            goto ilseq;
          if (ret != 2) abort();
          conv->istate = state;
          return count+2;
        } else
          goto ilseq;
      case STATE_JISX02131:
      case STATE_JISX02132:
        if (n < count+2)
          goto none;
        if (s[0] < 0x80 && s[1] < 0x80) {
          ucs4_t wc = jisx0213_to_ucs4(((state-STATE_JISX02131+1)<<8)+s[0],s[1]);
          if (wc) {
            if (wc < 0x80) {
              /* It's a combining character. */
              ucs4_t wc1 = jisx0213_to_ucs_combining[wc - 1][0];
              ucs4_t wc2 = jisx0213_to_ucs_combining[wc - 1][1];
              /* We cannot output two Unicode characters at once. So,
                 output the first character and buffer the second one. */
              *pwc = wc1;
              conv->istate = (wc2 << 3) | state;
            } else {
              *pwc = wc;
              conv->istate = state;
            }
            return count+2;
          }
        }
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
}