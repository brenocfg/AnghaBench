#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ucs4_t ;
typedef  void* state_t ;
typedef  TYPE_1__* conv_t ;
struct TYPE_4__ {void* istate; } ;

/* Variables and functions */
 int RET_ILSEQ ; 
 int RET_SHIFT_ILSEQ (unsigned int) ; 
 int RET_TOOFEW (unsigned int) ; 
 int /*<<< orphan*/  abort () ; 
 int gb2312_mbtowc (TYPE_1__*,scalar_t__*,unsigned char const*,int) ; 

__attribute__((used)) static int
hz_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  state_t state = conv->istate;
  unsigned int count = 0;
  unsigned char c;
  for (;;) {
    c = *s;
    if (c == '~') {
      if (n < count+2)
        goto none;
      c = s[1];
      if (state == 0) {
        if (c == '~') {
          *pwc = (ucs4_t) '~';
          conv->istate = state;
          return count+2;
        }
        if (c == '{') {
          state = 1;
          s += 2; count += 2;
          if (n < count+1)
            goto none;
          continue;
        }
        if (c == '\n') {
          s += 2; count += 2;
          if (n < count+1)
            goto none;
          continue;
        }
      } else {
        if (c == '}') {
          state = 0;
          s += 2; count += 2;
          if (n < count+1)
            goto none;
          continue;
        }
      }
      goto ilseq;
    }
    break;
  }
  if (state == 0) {
    *pwc = (ucs4_t) c;
    conv->istate = state;
    return count+1;
  } else {
    int ret;
    if (n < count+2)
      goto none;
    ret = gb2312_mbtowc(conv,pwc,s,2);
    if (ret == RET_ILSEQ)
      goto ilseq;
    if (ret != 2) abort();
    conv->istate = state;
    return count+2;
  }

none:
  conv->istate = state;
  return RET_TOOFEW(count);

ilseq:
  conv->istate = state;
  return RET_SHIFT_ILSEQ(count);
}