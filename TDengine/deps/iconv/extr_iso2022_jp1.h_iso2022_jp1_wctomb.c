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
typedef  int /*<<< orphan*/  ucs4_t ;
typedef  scalar_t__ state_t ;
typedef  TYPE_1__* conv_t ;
struct TYPE_7__ {scalar_t__ ostate; } ;

/* Variables and functions */
 unsigned char ESC ; 
 int RET_ILUNI ; 
 int RET_TOOSMALL ; 
 scalar_t__ STATE_ASCII ; 
 scalar_t__ STATE_JISX0201ROMAN ; 
 scalar_t__ STATE_JISX0208 ; 
 scalar_t__ STATE_JISX0212 ; 
 int /*<<< orphan*/  abort () ; 
 int ascii_wctomb (TYPE_1__*,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int jisx0201_wctomb (TYPE_1__*,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int jisx0208_wctomb (TYPE_1__*,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int jisx0212_wctomb (TYPE_1__*,unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
iso2022_jp1_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, int n)
{
  state_t state = conv->ostate;
  unsigned char buf[2];
  int ret;

  /* Try ASCII. */
  ret = ascii_wctomb(conv,buf,wc,1);
  if (ret != RET_ILUNI) {
    if (ret != 1) abort();
    if (buf[0] < 0x80) {
      int count = (state == STATE_ASCII ? 1 : 4);
      if (n < count)
        return RET_TOOSMALL;
      if (state != STATE_ASCII) {
        r[0] = ESC;
        r[1] = '(';
        r[2] = 'B';
        r += 3;
        state = STATE_ASCII;
      }
      r[0] = buf[0];
      conv->ostate = state;
      return count;
    }
  }

  /* Try JIS X 0201-1976 Roman. */
  ret = jisx0201_wctomb(conv,buf,wc,1);
  if (ret != RET_ILUNI) {
    if (ret != 1) abort();
    if (buf[0] < 0x80) {
      int count = (state == STATE_JISX0201ROMAN ? 1 : 4);
      if (n < count)
        return RET_TOOSMALL;
      if (state != STATE_JISX0201ROMAN) {
        r[0] = ESC;
        r[1] = '(';
        r[2] = 'J';
        r += 3;
        state = STATE_JISX0201ROMAN;
      }
      r[0] = buf[0];
      conv->ostate = state;
      return count;
    }
  }

  /* Try JIS X 0208-1990 in place of JIS X 0208-1978 and JIS X 0208-1983. */
  ret = jisx0208_wctomb(conv,buf,wc,2);
  if (ret != RET_ILUNI) {
    if (ret != 2) abort();
    if (buf[0] < 0x80 && buf[1] < 0x80) {
      int count = (state == STATE_JISX0208 ? 2 : 5);
      if (n < count)
        return RET_TOOSMALL;
      if (state != STATE_JISX0208) {
        r[0] = ESC;
        r[1] = '$';
        r[2] = 'B';
        r += 3;
        state = STATE_JISX0208;
      }
      r[0] = buf[0];
      r[1] = buf[1];
      conv->ostate = state;
      return count;
    }
  }

  /* Try JIS X 0212-1990. */
  ret = jisx0212_wctomb(conv,buf,wc,2);
  if (ret != RET_ILUNI) {
    if (ret != 2) abort();
    if (buf[0] < 0x80 && buf[1] < 0x80) {
      int count = (state == STATE_JISX0212 ? 2 : 6);
      if (n < count)
        return RET_TOOSMALL;
      if (state != STATE_JISX0212) {
        r[0] = ESC;
        r[1] = '$';
        r[2] = '(';
        r[3] = 'D';
        r += 4;
        state = STATE_JISX0212;
      }
      r[0] = buf[0];
      r[1] = buf[1];
      conv->ostate = state;
      return count;
    }
  }

  return RET_ILUNI;
}