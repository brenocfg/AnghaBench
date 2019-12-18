#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int ucs4_t ;
typedef  void* state_t ;
typedef  TYPE_1__* conv_t ;
struct TYPE_13__ {void* istate; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMBINE_STATE ; 
 unsigned char ESC ; 
 int RET_ILSEQ ; 
 int RET_SHIFT_ILSEQ (int) ; 
 int RET_TOOFEW (int) ; 
 unsigned char SI ; 
 unsigned char SO ; 
 int /*<<< orphan*/  SPLIT_STATE ; 
#define  STATE2_DESIGNATED_CNS11643_1 141 
#define  STATE2_DESIGNATED_GB2312 140 
#define  STATE2_DESIGNATED_ISO_IR_165 139 
#define  STATE2_NONE 138 
#define  STATE3_DESIGNATED_CNS11643_2 137 
#define  STATE3_NONE 136 
#define  STATE4_DESIGNATED_CNS11643_3 135 
#define  STATE4_DESIGNATED_CNS11643_4 134 
#define  STATE4_DESIGNATED_CNS11643_5 133 
#define  STATE4_DESIGNATED_CNS11643_6 132 
#define  STATE4_DESIGNATED_CNS11643_7 131 
#define  STATE4_NONE 130 
#define  STATE_ASCII 129 
#define  STATE_TWOBYTE 128 
 int /*<<< orphan*/  abort () ; 
 int ascii_mbtowc (TYPE_1__*,int*,unsigned char const*,int) ; 
 int cns11643_1_mbtowc (TYPE_1__*,int*,unsigned char const*,int) ; 
 int cns11643_2_mbtowc (TYPE_1__*,int*,unsigned char const*,int) ; 
 int cns11643_3_mbtowc (TYPE_1__*,int*,unsigned char const*,int) ; 
 int cns11643_4_mbtowc (TYPE_1__*,int*,unsigned char const*,int) ; 
 int cns11643_5_mbtowc (TYPE_1__*,int*,unsigned char const*,int) ; 
 int cns11643_6_mbtowc (TYPE_1__*,int*,unsigned char const*,int) ; 
 int cns11643_7_mbtowc (TYPE_1__*,int*,unsigned char const*,int) ; 
 int gb2312_mbtowc (TYPE_1__*,int*,unsigned char const*,int) ; 
 int isoir165_mbtowc (TYPE_1__*,int*,unsigned char const*,int) ; 
 int state1 ; 
 scalar_t__ state2 ; 
 int state3 ; 
 int state4 ; 

__attribute__((used)) static int
iso2022_cn_ext_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
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
          if (s[3] == 'E') {
            state2 = STATE2_DESIGNATED_ISO_IR_165;
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
        if (s[2] == '+') {
          if (s[3] == 'I') {
            state4 = STATE4_DESIGNATED_CNS11643_3;
            s += 4; count += 4;
            if (n < count+1)
              goto none;
            continue;
          }
          if (s[3] == 'J') {
            state4 = STATE4_DESIGNATED_CNS11643_4;
            s += 4; count += 4;
            if (n < count+1)
              goto none;
            continue;
          }
          if (s[3] == 'K') {
            state4 = STATE4_DESIGNATED_CNS11643_5;
            s += 4; count += 4;
            if (n < count+1)
              goto none;
            continue;
          }
          if (s[3] == 'L') {
            state4 = STATE4_DESIGNATED_CNS11643_6;
            s += 4; count += 4;
            if (n < count+1)
              goto none;
            continue;
          }
          if (s[3] == 'M') {
            state4 = STATE4_DESIGNATED_CNS11643_7;
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
      if (s[1] == 'O') {
        switch (state4) {
          case STATE4_NONE:
            goto ilseq;
          case STATE4_DESIGNATED_CNS11643_3:
            if (s[2] < 0x80 && s[3] < 0x80) {
              int ret = cns11643_3_mbtowc(conv,pwc,s+2,2);
              if (ret == RET_ILSEQ)
                goto ilseq;
              if (ret != 2) abort();
              COMBINE_STATE;
              conv->istate = state;
              return count+4;
            } else
              goto ilseq;
          case STATE4_DESIGNATED_CNS11643_4:
            if (s[2] < 0x80 && s[3] < 0x80) {
              int ret = cns11643_4_mbtowc(conv,pwc,s+2,2);
              if (ret == RET_ILSEQ)
                goto ilseq;
              if (ret != 2) abort();
              COMBINE_STATE;
              conv->istate = state;
              return count+4;
            } else
              goto ilseq;
          case STATE4_DESIGNATED_CNS11643_5:
            if (s[2] < 0x80 && s[3] < 0x80) {
              int ret = cns11643_5_mbtowc(conv,pwc,s+2,2);
              if (ret == RET_ILSEQ)
                goto ilseq;
              if (ret != 2) abort();
              COMBINE_STATE;
              conv->istate = state;
              return count+4;
            } else
              goto ilseq;
          case STATE4_DESIGNATED_CNS11643_6:
            if (s[2] < 0x80 && s[3] < 0x80) {
              int ret = cns11643_6_mbtowc(conv,pwc,s+2,2);
              if (ret == RET_ILSEQ)
                goto ilseq;
              if (ret != 2) abort();
              COMBINE_STATE;
              conv->istate = state;
              return count+4;
            } else
              goto ilseq;
          case STATE4_DESIGNATED_CNS11643_7:
            if (s[2] < 0x80 && s[3] < 0x80) {
              int ret = cns11643_7_mbtowc(conv,pwc,s+2,2);
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
      if (state2 != STATE2_DESIGNATED_GB2312 && state2 != STATE2_DESIGNATED_CNS11643_1 && state2 != STATE2_DESIGNATED_ISO_IR_165)
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
          state2 = STATE2_NONE; state3 = STATE3_NONE; state4 = STATE3_NONE;
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
          case STATE2_DESIGNATED_ISO_IR_165:
            ret = isoir165_mbtowc(conv,pwc,s,2); break;
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