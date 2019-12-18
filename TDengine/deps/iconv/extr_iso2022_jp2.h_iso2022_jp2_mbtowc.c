#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int ucs4_t ;
typedef  void* state_t ;
typedef  TYPE_1__* conv_t ;
struct TYPE_11__ {void* istate; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMBINE_STATE ; 
 unsigned char ESC ; 
 int RET_ILSEQ ; 
 int RET_SHIFT_ILSEQ (int) ; 
 int RET_TOOFEW (int) ; 
 int /*<<< orphan*/  SPLIT_STATE ; 
#define  STATE_ASCII 137 
#define  STATE_G2_ISO8859_1 136 
#define  STATE_G2_ISO8859_7 135 
#define  STATE_G2_NONE 134 
#define  STATE_GB2312 133 
#define  STATE_JISX0201KATAKANA 132 
#define  STATE_JISX0201ROMAN 131 
#define  STATE_JISX0208 130 
#define  STATE_JISX0212 129 
#define  STATE_KSC5601 128 
 int /*<<< orphan*/  abort () ; 
 int ascii_mbtowc (TYPE_1__*,int*,unsigned char const*,int) ; 
 int gb2312_mbtowc (TYPE_1__*,int*,unsigned char const*,int) ; 
 int iso8859_1_mbtowc (TYPE_1__*,int*,unsigned char*,int) ; 
 int iso8859_7_mbtowc (TYPE_1__*,int*,unsigned char*,int) ; 
 int jisx0201_mbtowc (TYPE_1__*,int*,unsigned char const*,int) ; 
 int jisx0208_mbtowc (TYPE_1__*,int*,unsigned char const*,int) ; 
 int jisx0212_mbtowc (TYPE_1__*,int*,unsigned char const*,int) ; 
 int ksc5601_mbtowc (TYPE_1__*,int*,unsigned char const*,int) ; 
 int state1 ; 
 int state2 ; 

__attribute__((used)) static int
iso2022_jp2_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  state_t state = conv->istate;
  SPLIT_STATE;
  int count = 0;
  unsigned char c;
  for (;;) {
    c = *s;
    if (c == ESC) {
      if (n < count+3)
        goto none;
      if (s[1] == '(') {
        if (s[2] == 'B') {
          state1 = STATE_ASCII;
          s += 3; count += 3;
          if (n < count+1)
            goto none;
          continue;
        }
        if (s[2] == 'J') {
          state1 = STATE_JISX0201ROMAN;
          s += 3; count += 3;
          if (n < count+1)
            goto none;
          continue;
        }
        if (s[2] == 'I') {
          state1 = STATE_JISX0201KATAKANA;
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
          state1 = STATE_JISX0208;
          s += 3; count += 3;
          if (n < count+1)
            goto none;
          continue;
        }
        if (s[2] == 'A') {
          state1 = STATE_GB2312;
          s += 3; count += 3;
          if (n < count+1)
            goto none;
          continue;
        }
        if (s[2] == '(') {
          if (n < count+4)
            goto none;
          if (s[3] == 'D') {
            state1 = STATE_JISX0212;
            s += 4; count += 4;
            if (n < count+1)
              goto none;
            continue;
          }
          if (s[3] == 'C') {
            state1 = STATE_KSC5601;
            s += 4; count += 4;
            if (n < count+1)
              goto none;
            continue;
          }
          goto ilseq;
        }
        goto ilseq;
      }
      if (s[1] == '.') {
        if (n < count+3)
          goto none;
        if (s[2] == 'A') {
          state2 = STATE_G2_ISO8859_1;
          s += 3; count += 3;
          if (n < count+1)
            goto none;
          continue;
        }
        if (s[2] == 'F') {
          state2 = STATE_G2_ISO8859_7;
          s += 3; count += 3;
          if (n < count+1)
            goto none;
          continue;
        }
        goto ilseq;
      }
      if (s[1] == 'N') {
        switch (state2) {
          case STATE_G2_NONE:
            goto ilseq;
          case STATE_G2_ISO8859_1:
            if (s[2] < 0x80) {
              unsigned char buf = s[2]+0x80;
              int ret = iso8859_1_mbtowc(conv,pwc,&buf,1);
              if (ret == RET_ILSEQ)
                goto ilseq;
              if (ret != 1) abort();
              COMBINE_STATE;
              conv->istate = state;
              return count+3;
            } else
              goto ilseq;
          case STATE_G2_ISO8859_7:
            if (s[2] < 0x80) {
              unsigned char buf = s[2]+0x80;
              int ret = iso8859_7_mbtowc(conv,pwc,&buf,1);
              if (ret == RET_ILSEQ)
                goto ilseq;
              if (ret != 1) abort();
              COMBINE_STATE;
              conv->istate = state;
              return count+3;
            } else
              goto ilseq;
          default: abort();
        }
      }
      goto ilseq;
    }
    break;
  }
  switch (state1) {
    case STATE_ASCII:
      if (c < 0x80) {
        int ret = ascii_mbtowc(conv,pwc,s,1);
        if (ret == RET_ILSEQ)
          goto ilseq;
        if (ret != 1) abort();
        if (*pwc == 0x000a || *pwc == 0x000d)
          state2 = STATE_G2_NONE;
        COMBINE_STATE;
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
        if (*pwc == 0x000a || *pwc == 0x000d)
          state2 = STATE_G2_NONE;
        COMBINE_STATE;
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
        COMBINE_STATE;
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
        COMBINE_STATE;
        conv->istate = state;
        return count+2;
      } else
        goto ilseq;
    case STATE_JISX0212:
      if (n < count+2)
        goto none;
      if (s[0] < 0x80 && s[1] < 0x80) {
        int ret = jisx0212_mbtowc(conv,pwc,s,2);
        if (ret == RET_ILSEQ)
          goto ilseq;
        if (ret != 2) abort();
        COMBINE_STATE;
        conv->istate = state;
        return count+2;
      } else
        goto ilseq;
    case STATE_GB2312:
      if (n < count+2)
        goto none;
      if (s[0] < 0x80 && s[1] < 0x80) {
        int ret = gb2312_mbtowc(conv,pwc,s,2);
        if (ret == RET_ILSEQ)
          goto ilseq;
        if (ret != 2) abort();
        COMBINE_STATE;
        conv->istate = state;
        return count+2;
      } else
        goto ilseq;
    case STATE_KSC5601:
      if (n < count+2)
        goto none;
      if (s[0] < 0x80 && s[1] < 0x80) {
        int ret = ksc5601_mbtowc(conv,pwc,s,2);
        if (ret == RET_ILSEQ)
          goto ilseq;
        if (ret != 2) abort();
        COMBINE_STATE;
        conv->istate = state;
        return count+2;
      } else
        goto ilseq;
    default: abort();
  }

none:
  COMBINE_STATE;
  conv->istate = state;
  return RET_TOOFEW(count);

ilseq:
  COMBINE_STATE;
  conv->istate = state;
  return RET_SHIFT_ILSEQ(count);
}