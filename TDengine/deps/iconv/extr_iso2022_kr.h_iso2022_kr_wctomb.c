#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ucs4_t ;
typedef  void* state_t ;
typedef  TYPE_1__* conv_t ;
struct TYPE_5__ {void* ostate; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMBINE_STATE ; 
 unsigned char ESC ; 
 int RET_ILUNI ; 
 int RET_TOOSMALL ; 
 unsigned char SI ; 
 unsigned char SO ; 
 int /*<<< orphan*/  SPLIT_STATE ; 
 scalar_t__ STATE2_DESIGNATED_KSC5601 ; 
 scalar_t__ STATE2_NONE ; 
 scalar_t__ STATE_ASCII ; 
 scalar_t__ STATE_TWOBYTE ; 
 int /*<<< orphan*/  abort () ; 
 int ascii_wctomb (TYPE_1__*,unsigned char*,int,int) ; 
 int ksc5601_wctomb (TYPE_1__*,unsigned char*,int,int) ; 
 scalar_t__ state1 ; 
 scalar_t__ state2 ; 

__attribute__((used)) static int
iso2022_kr_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, int n)
{
  state_t state = conv->ostate;
  SPLIT_STATE;
  unsigned char buf[2];
  int ret;

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
      if (wc == 0x000a || wc == 0x000d)
        state2 = STATE2_NONE;
      COMBINE_STATE;
      conv->ostate = state;
      return count;
    }
  }

  /* Try KS C 5601-1992. */
  ret = ksc5601_wctomb(conv,buf,wc,2);
  if (ret != RET_ILUNI) {
    if (ret != 2) abort();
    if (buf[0] < 0x80 && buf[1] < 0x80) {
      int count = (state2 == STATE2_DESIGNATED_KSC5601 ? 0 : 4) + (state1 == STATE_TWOBYTE ? 0 : 1) + 2;
      if (n < count)
        return RET_TOOSMALL;
      if (state2 != STATE2_DESIGNATED_KSC5601) {
        r[0] = ESC;
        r[1] = '$';
        r[2] = ')';
        r[3] = 'C';
        r += 4;
        state2 = STATE2_DESIGNATED_KSC5601;
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