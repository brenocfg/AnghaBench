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
typedef  int ucs4_t ;
typedef  scalar_t__ state_t ;
typedef  TYPE_1__* conv_t ;
struct TYPE_9__ {scalar_t__ ostate; } ;

/* Variables and functions */
 unsigned char ESC ; 
 int RET_ILUNI ; 
 int RET_TOOSMALL ; 
 scalar_t__ STATE_ASCII ; 
 scalar_t__ STATE_JISX0201KATAKANA ; 
 scalar_t__ STATE_JISX0208MS ; 
 scalar_t__ STATE_JISX0212MS ; 
 int /*<<< orphan*/  abort () ; 
 int ascii_wctomb (TYPE_1__*,unsigned char*,int,int) ; 
 int cp50221_0208_ext_wctomb (TYPE_1__*,unsigned char*,int,int) ; 
 int cp50221_0212_ext_wctomb (TYPE_1__*,unsigned char*,int,int) ; 
 int jisx0201_wctomb (TYPE_1__*,unsigned char*,int,int) ; 
 int jisx0208_wctomb (TYPE_1__*,unsigned char*,int,int) ; 
 int jisx0212_wctomb (TYPE_1__*,unsigned char*,int,int) ; 

__attribute__((used)) static int
iso2022_jpms_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
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

  /* Try JIS X 0201-1976 Katakana. */
  ret = jisx0201_wctomb(conv,buf,wc,1);
  if (ret != RET_ILUNI) {
    if (ret != 1) abort();
    if (buf[0] >= 0x80) {
      int count = (state == STATE_JISX0201KATAKANA ? 1 : 4);
      if (n < count)
        return RET_TOOSMALL;
      if (state != STATE_JISX0201KATAKANA) {
        r[0] = ESC;
        r[1] = '(';
        r[2] = 'I';
        r += 3;
        state = STATE_JISX0201KATAKANA;
      }
      r[0] = buf[0]-0x80;
      conv->ostate = state;
      return count;
    }
  }

  /* Try JIS X 0208-1990, in place of JIS X 0208-1978 and JIS X 0208-1983,
     and the extensions mentioned above.  */
  if (wc >= 0xe000 && wc < 0xe3ac) {
    unsigned short i = wc - 0xe000;
    buf[0] = (i / 94) + 0x75;
    buf[1] = (i % 94) + 0x21;
    ret = 2;
  } else {
    ret = jisx0208_wctomb(conv,buf,wc,2);
    if (ret == RET_ILUNI) {
      /* Extension of JIS X 0208.  */
      unsigned char i;
      ret = cp50221_0208_ext_wctomb(conv,&i,wc,1);
      if (ret == 1) {
        buf[0] = 0x2d;
        buf[1] = i-1 + 0x21;
        ret = 2;
      } else if (wc == 0x663B) {
        buf[0] = 0x7a;
        buf[1] = 0x36;
        ret = 2;
      } else if (wc == 0xffe2) {
        buf[0] = 0x7c;
        buf[1] = 0x7b;
        ret = 2;
      } else if (wc == 0xffe4) {
        buf[0] = 0x7c;
        buf[1] = 0x7c;
        ret = 2;
      }
    }
  }
  if (ret != RET_ILUNI) {
    if (ret != 2) abort();
    if (buf[0] < 0x80 && buf[1] < 0x80) {
      int count = (state == STATE_JISX0208MS ? 2 : 5);
      if (n < count)
        return RET_TOOSMALL;
      if (state != STATE_JISX0208MS) {
        r[0] = ESC;
        r[1] = '$';
        r[2] = 'B';
        r += 3;
        state = STATE_JISX0208MS;
      }
      r[0] = buf[0];
      r[1] = buf[1];
      conv->ostate = state;
      return count;
    }
  }

  /* Try JIS X 0212-1990 and the extensions mentioned above. */
  if (wc >= 0xe3ac && wc < 0xe758) {
    unsigned short i = wc - 0xe3ac;
    buf[0] = (i / 94) + 0x75;
    buf[1] = (i % 94) + 0x21;
    ret = 2;
  } else {
    ret = jisx0212_wctomb(conv,buf,wc,2);
    if (ret == RET_ILUNI) {
      /* Extension of JIS X 0212.  */
      unsigned char i;
      ret = cp50221_0212_ext_wctomb(conv,&i,wc,1);
      if (ret == 1) {
        i -= 1;
        buf[0] = (i / 94) + 0x73;
        buf[1] = (i % 94) + 0x21;
        ret = 2;
      }
    }
  }
  if (ret != RET_ILUNI) {
    if (ret != 2) abort();
    if (buf[0] < 0x80 && buf[1] < 0x80) {
      int count = (state == STATE_JISX0212MS ? 2 : 6);
      if (n < count)
        return RET_TOOSMALL;
      if (state != STATE_JISX0212MS) {
        r[0] = ESC;
        r[1] = '$';
        r[2] = '(';
        r[3] = 'D';
        r += 4;
        state = STATE_JISX0212MS;
      }
      r[0] = buf[0];
      r[1] = buf[1];
      conv->ostate = state;
      return count;
    }
  }

  return RET_ILUNI;
}