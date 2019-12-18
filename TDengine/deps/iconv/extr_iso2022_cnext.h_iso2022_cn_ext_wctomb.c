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
struct TYPE_7__ {void* ostate; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMBINE_STATE ; 
 unsigned char ESC ; 
 int RET_ILUNI ; 
 int RET_TOOSMALL ; 
 unsigned char SI ; 
 unsigned char SO ; 
 int /*<<< orphan*/  SPLIT_STATE ; 
 scalar_t__ STATE2_DESIGNATED_CNS11643_1 ; 
 scalar_t__ STATE2_DESIGNATED_GB2312 ; 
 scalar_t__ STATE2_DESIGNATED_ISO_IR_165 ; 
 scalar_t__ STATE2_NONE ; 
 scalar_t__ STATE3_DESIGNATED_CNS11643_2 ; 
 scalar_t__ STATE3_NONE ; 
 scalar_t__ STATE4_DESIGNATED_CNS11643_3 ; 
 scalar_t__ STATE4_DESIGNATED_CNS11643_4 ; 
 scalar_t__ STATE4_DESIGNATED_CNS11643_5 ; 
 scalar_t__ STATE4_DESIGNATED_CNS11643_6 ; 
 scalar_t__ STATE4_DESIGNATED_CNS11643_7 ; 
 scalar_t__ STATE_ASCII ; 
 scalar_t__ STATE_TWOBYTE ; 
 int /*<<< orphan*/  abort () ; 
 int ascii_wctomb (TYPE_1__*,unsigned char*,int,int) ; 
 int cns11643_wctomb (TYPE_1__*,unsigned char*,int,int) ; 
 int gb2312_wctomb (TYPE_1__*,unsigned char*,int,int) ; 
 int isoir165_wctomb (TYPE_1__*,unsigned char*,int,int) ; 
 scalar_t__ state1 ; 
 scalar_t__ state2 ; 
 scalar_t__ state3 ; 
 scalar_t__ state4 ; 

__attribute__((used)) static int
iso2022_cn_ext_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, int n)
{
  state_t state = conv->ostate;
  SPLIT_STATE;
  unsigned char buf[3];
  int ret;

  /* There is no need to handle Unicode 3.1 tag characters and to look for
     "zh-CN" or "zh-TW" tags, because GB2312 and CNS11643 are disjoint. */

  /* Try ASCII. */
  ret = ascii_wctomb(conv,buf,wc,1);
  if (ret != RET_ILUNI) {
    if (ret != 1) abort();
    if (buf[0] < 0x80) {
      int count = (state1 == STATE_ASCII ? 1 : 2);
      if (n < count)
        return RET_TOOSMALL;
      if (state1 != STATE_ASCII) {
        r[0] = SI;
        r += 1;
        state1 = STATE_ASCII;
      }
      r[0] = buf[0];
      if (wc == 0x000a || wc == 0x000d) {
        state2 = STATE2_NONE; state3 = STATE3_NONE; state4 = STATE3_NONE;
      }
      COMBINE_STATE;
      conv->ostate = state;
      return count;
    }
  }

  /* Try GB 2312-1980. */
  ret = gb2312_wctomb(conv,buf,wc,2);
  if (ret != RET_ILUNI) {
    if (ret != 2) abort();
    if (buf[0] < 0x80 && buf[1] < 0x80) {
      int count = (state2 == STATE2_DESIGNATED_GB2312 ? 0 : 4) + (state1 == STATE_TWOBYTE ? 0 : 1) + 2;
      if (n < count)
        return RET_TOOSMALL;
      if (state2 != STATE2_DESIGNATED_GB2312) {
        r[0] = ESC;
        r[1] = '$';
        r[2] = ')';
        r[3] = 'A';
        r += 4;
        state2 = STATE2_DESIGNATED_GB2312;
      }
      if (state1 != STATE_TWOBYTE) {
        r[0] = SO;
        r += 1;
        state1 = STATE_TWOBYTE;
      }
      r[0] = buf[0];
      r[1] = buf[1];
      COMBINE_STATE;
      conv->ostate = state;
      return count;
    }
  }

  ret = cns11643_wctomb(conv,buf,wc,3);
  if (ret != RET_ILUNI) {
    if (ret != 3) abort();

    /* Try CNS 11643-1992 Plane 1. */
    if (buf[0] == 1 && buf[1] < 0x80 && buf[2] < 0x80) {
      int count = (state2 == STATE2_DESIGNATED_CNS11643_1 ? 0 : 4) + (state1 == STATE_TWOBYTE ? 0 : 1) + 2;
      if (n < count)
        return RET_TOOSMALL;
      if (state2 != STATE2_DESIGNATED_CNS11643_1) {
        r[0] = ESC;
        r[1] = '$';
        r[2] = ')';
        r[3] = 'G';
        r += 4;
        state2 = STATE2_DESIGNATED_CNS11643_1;
      }
      if (state1 != STATE_TWOBYTE) {
        r[0] = SO;
        r += 1;
        state1 = STATE_TWOBYTE;
      }
      r[0] = buf[1];
      r[1] = buf[2];
      COMBINE_STATE;
      conv->ostate = state;
      return count;
    }

    /* Try CNS 11643-1992 Plane 2. */
    if (buf[0] == 2 && buf[1] < 0x80 && buf[2] < 0x80) {
      int count = (state3 == STATE3_DESIGNATED_CNS11643_2 ? 0 : 4) + 4;
      if (n < count)
        return RET_TOOSMALL;
      if (state3 != STATE3_DESIGNATED_CNS11643_2) {
        r[0] = ESC;
        r[1] = '$';
        r[2] = '*';
        r[3] = 'H';
        r += 4;
        state3 = STATE3_DESIGNATED_CNS11643_2;
      }
      r[0] = ESC;
      r[1] = 'N';
      r[2] = buf[1];
      r[3] = buf[2];
      COMBINE_STATE;
      conv->ostate = state;
      return count;
    }

    /* Try CNS 11643-1992 Plane 3. */
    if (buf[0] == 3 && buf[1] < 0x80 && buf[2] < 0x80) {
      int count = (state4 == STATE4_DESIGNATED_CNS11643_3 ? 0 : 4) + 4;
      if (n < count)
        return RET_TOOSMALL;
      if (state4 != STATE4_DESIGNATED_CNS11643_3) {
        r[0] = ESC;
        r[1] = '$';
        r[2] = '+';
        r[3] = 'I';
        r += 4;
        state4 = STATE4_DESIGNATED_CNS11643_3;
      }
      r[0] = ESC;
      r[1] = 'O';
      r[2] = buf[1];
      r[3] = buf[2];
      COMBINE_STATE;
      conv->ostate = state;
      return count;
    }

    /* Try CNS 11643-1992 Plane 4. */
    if (buf[0] == 4 && buf[1] < 0x80 && buf[2] < 0x80) {
      int count = (state4 == STATE4_DESIGNATED_CNS11643_4 ? 0 : 4) + 4;
      if (n < count)
        return RET_TOOSMALL;
      if (state4 != STATE4_DESIGNATED_CNS11643_4) {
        r[0] = ESC;
        r[1] = '$';
        r[2] = '+';
        r[3] = 'J';
        r += 4;
        state4 = STATE4_DESIGNATED_CNS11643_4;
      }
      r[0] = ESC;
      r[1] = 'O';
      r[2] = buf[1];
      r[3] = buf[2];
      COMBINE_STATE;
      conv->ostate = state;
      return count;
    }

    /* Try CNS 11643-1992 Plane 5. */
    if (buf[0] == 5 && buf[1] < 0x80 && buf[2] < 0x80) {
      int count = (state4 == STATE4_DESIGNATED_CNS11643_5 ? 0 : 4) + 4;
      if (n < count)
        return RET_TOOSMALL;
      if (state4 != STATE4_DESIGNATED_CNS11643_5) {
        r[0] = ESC;
        r[1] = '$';
        r[2] = '+';
        r[3] = 'K';
        r += 4;
        state4 = STATE4_DESIGNATED_CNS11643_5;
      }
      r[0] = ESC;
      r[1] = 'O';
      r[2] = buf[1];
      r[3] = buf[2];
      COMBINE_STATE;
      conv->ostate = state;
      return count;
    }

    /* Try CNS 11643-1992 Plane 6. */
    if (buf[0] == 6 && buf[1] < 0x80 && buf[2] < 0x80) {
      int count = (state4 == STATE4_DESIGNATED_CNS11643_6 ? 0 : 4) + 4;
      if (n < count)
        return RET_TOOSMALL;
      if (state4 != STATE4_DESIGNATED_CNS11643_6) {
        r[0] = ESC;
        r[1] = '$';
        r[2] = '+';
        r[3] = 'L';
        r += 4;
        state4 = STATE4_DESIGNATED_CNS11643_6;
      }
      r[0] = ESC;
      r[1] = 'O';
      r[2] = buf[1];
      r[3] = buf[2];
      COMBINE_STATE;
      conv->ostate = state;
      return count;
    }

    /* Try CNS 11643-1992 Plane 7. */
    if (buf[0] == 7 && buf[1] < 0x80 && buf[2] < 0x80) {
      int count = (state4 == STATE4_DESIGNATED_CNS11643_7 ? 0 : 4) + 4;
      if (n < count)
        return RET_TOOSMALL;
      if (state4 != STATE4_DESIGNATED_CNS11643_7) {
        r[0] = ESC;
        r[1] = '$';
        r[2] = '+';
        r[3] = 'M';
        r += 4;
        state4 = STATE4_DESIGNATED_CNS11643_7;
      }
      r[0] = ESC;
      r[1] = 'O';
      r[2] = buf[1];
      r[3] = buf[2];
      COMBINE_STATE;
      conv->ostate = state;
      return count;
    }

  }

  /* Try ISO-IR-165. */
  ret = isoir165_wctomb(conv,buf,wc,2);
  if (ret != RET_ILUNI) {
    if (ret != 2) abort();
    if (buf[0] < 0x80 && buf[1] < 0x80) {
      int count = (state2 == STATE2_DESIGNATED_ISO_IR_165 ? 0 : 4) + (state1 == STATE_TWOBYTE ? 0 : 1) + 2;
      if (n < count)
        return RET_TOOSMALL;
      if (state2 != STATE2_DESIGNATED_ISO_IR_165) {
        r[0] = ESC;
        r[1] = '$';
        r[2] = ')';
        r[3] = 'E';
        r += 4;
        state2 = STATE2_DESIGNATED_ISO_IR_165;
      }
      if (state1 != STATE_TWOBYTE) {
        r[0] = SO;
        r += 1;
        state1 = STATE_TWOBYTE;
      }
      r[0] = buf[0];
      r[1] = buf[1];
      COMBINE_STATE;
      conv->ostate = state;
      return count;
    }
  }

  return RET_ILUNI;
}