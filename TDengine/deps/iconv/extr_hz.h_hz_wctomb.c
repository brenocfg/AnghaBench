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
typedef  int /*<<< orphan*/  ucs4_t ;
typedef  int state_t ;
typedef  TYPE_1__* conv_t ;
struct TYPE_5__ {int ostate; } ;

/* Variables and functions */
 int RET_ILUNI ; 
 int RET_TOOSMALL ; 
 int /*<<< orphan*/  abort () ; 
 int ascii_wctomb (TYPE_1__*,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int gb2312_wctomb (TYPE_1__*,unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
hz_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, int n)
{
  state_t state = conv->ostate;
  unsigned char buf[2];
  int ret;

  /* Code set 0 (ASCII or GB 1988-89) */
  ret = ascii_wctomb(conv,buf,wc,1);
  if (ret != RET_ILUNI) {
    if (ret != 1) abort();
    if (buf[0] < 0x80) {
      int count = (state ? 3 : 1);
      if (n < count)
        return RET_TOOSMALL;
      if (state) {
        r[0] = '~';
        r[1] = '}';
        r += 2;
        state = 0;
      }
      r[0] = buf[0];
      conv->ostate = state;
      return count;
    }
  }

  /* Code set 1 (GB 2312-1980) */
  ret = gb2312_wctomb(conv,buf,wc,2);
  if (ret != RET_ILUNI) {
    if (ret != 2) abort();
    if (buf[0] < 0x80 && buf[1] < 0x80) {
      int count = (state ? 2 : 4);
      if (n < count)
        return RET_TOOSMALL;
      if (!state) {
        r[0] = '~';
        r[1] = '{';
        r += 2;
        state = 1;
      }
      r[0] = buf[0];
      r[1] = buf[1];
      conv->ostate = state;
      return count;
    }
  }

  return RET_ILUNI;
}