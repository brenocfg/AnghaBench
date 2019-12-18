#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ucs4_t ;
typedef  void* state_t ;
typedef  TYPE_1__* conv_t ;
struct TYPE_7__ {void* istate; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMBINE_STATE ; 
 unsigned char ESC ; 
 int RET_ILSEQ ; 
 int RET_SHIFT_ILSEQ (int) ; 
 int RET_TOOFEW (int) ; 
 unsigned char SI ; 
 unsigned char SO ; 
 int /*<<< orphan*/  SPLIT_STATE ; 
#define  STATE2_DESIGNATED_CNS11643_1 134 
#define  STATE2_DESIGNATED_GB2312 133 
#define  STATE2_NONE 132 
#define  STATE3_DESIGNATED_CNS11643_2 131 
#define  STATE3_NONE 130 
#define  STATE_ASCII 129 
#define  STATE_TWOBYTE 128 
 int /*<<< orphan*/  abort () ; 
 int ascii_mbtowc (TYPE_1__*,int*,unsigned char const*,int) ; 
 int cns11643_1_mbtowc (TYPE_1__*,int*,unsigned char const*,int) ; 
 int cns11643_2_mbtowc (TYPE_1__*,int*,unsigned char const*,int) ; 
 int gb2312_mbtowc (TYPE_1__*,int*,unsigned char const*,int) ; 
 int state1 ; 
 scalar_t__ state2 ; 
 int state3 ; 

__attribute__((used)) static int
iso2022_cn_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  state_t state = conv->istate;
  SPLIT_STATE;
  int count = 0;
  unsigned char c;
  for (;;) {
    c = *s;
    if (c == ESC) {
      if (n < count+4)
        goto none;
      if (s[1] == '$') {
        if (s[2] == ')') {
          if (s[3] == 'A') {
            state2 = STATE2_DESIGNATED_GB2312;
            s += 4; count += 4;
            if (n < count+1)
              goto none;
            continue;
          }
          if (s[3] == 'G') {
            state2 = STATE2_DESIGNATED_CNS11643_1;
            s += 4; count += 4;
            if (n < count+1)
              goto none;
            continue;
          }
        }
        if (s[2] == '*') {
          if (s[3] == 'H') {
            state3 = STATE3_DESIGNATED_CNS11643_2;
            s += 4; count += 4;
            if (n < count+1)
              goto none;
            continue;
          }
        }
      }
      if (s[1] == 'N') {
        switch (state3) {
          case STATE3_NONE:
            goto ilseq;
          case STATE3_DESIGNATED_CNS11643_2:
            if (s[2] < 0x80 && s[3] < 0x80) {
              int ret = cns11643_2_mbtowc(conv,pwc,s+2,2);
              if (ret == RET_ILSEQ)
                goto ilseq;
              if (ret != 2) abort();
              COMBINE_STATE;
              conv->istate = state;
              return count+4;
            } else
              goto ilseq;
          default: abort();
        }
      }
      goto ilseq;
    }
    if (c == SO) {
      if (state2 != STATE2_DESIGNATED_GB2312 && state2 != STATE2_DESIGNATED_CNS11643_1)
        goto ilseq;
      state1 = STATE_TWOBYTE;
      s++; count++;
      if (n < count+1)
        goto none;
      continue;
    }
    if (c == SI) {
      state1 = STATE_ASCII;
      s++; count++;
      if (n < count+1)
        goto none;
      continue;
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
        if (*pwc == 0x000a || *pwc == 0x000d) {
          state2 = STATE2_NONE; state3 = STATE3_NONE;
        }
        COMBINE_STATE;
        conv->istate = state;
        return count+1;
      } else
        goto ilseq;
    case STATE_TWOBYTE:
      if (n < count+2)
        goto none;
      if (s[0] < 0x80 && s[1] < 0x80) {
        int ret;
        switch (state2) {
          case STATE2_NONE:
            goto ilseq;
          case STATE2_DESIGNATED_GB2312:
            ret = gb2312_mbtowc(conv,pwc,s,2); break;
          case STATE2_DESIGNATED_CNS11643_1:
            ret = cns11643_1_mbtowc(conv,pwc,s,2); break;
          default: abort();
        }
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