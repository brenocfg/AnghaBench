#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ucs4_t ;
typedef  TYPE_1__* conv_t ;
struct TYPE_7__ {unsigned int idx; unsigned int len; } ;
struct TYPE_6__ {unsigned short base; unsigned short composed; } ;
struct TYPE_5__ {unsigned short istate; } ;

/* Variables and functions */
 int RET_ILSEQ ; 
 int RET_TOOFEW (int) ; 
 int /*<<< orphan*/  abort () ; 
 unsigned short* cp1258_2uni ; 
 unsigned short* cp1258_comp_bases ; 
 TYPE_3__* viet_comp_table ; 
 TYPE_2__* viet_comp_table_data ; 

__attribute__((used)) static int
cp1258_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  unsigned char c = *s;
  unsigned short wc;
  unsigned short last_wc;
  if (c < 0x80) {
    wc = c;
  } else {
    wc = cp1258_2uni[c-0x80];
    if (wc == 0xfffd)
      return RET_ILSEQ;
  }
  last_wc = conv->istate;
  if (last_wc) {
    if (wc >= 0x0300 && wc < 0x0340) {
      /* See whether last_wc and wc can be combined. */
      unsigned int k;
      unsigned int i1, i2;
      switch (wc) {
        case 0x0300: k = 0; break;
        case 0x0301: k = 1; break;
        case 0x0303: k = 2; break;
        case 0x0309: k = 3; break;
        case 0x0323: k = 4; break;
        default: abort();
      }
      i1 = viet_comp_table[k].idx;
      i2 = i1 + viet_comp_table[k].len-1;
      if (last_wc >= viet_comp_table_data[i1].base
          && last_wc <= viet_comp_table_data[i2].base) {
        unsigned int i;
        for (;;) {
          i = (i1+i2)>>1;
          if (last_wc == viet_comp_table_data[i].base)
            break;
          if (last_wc < viet_comp_table_data[i].base) {
            if (i1 == i)
              goto not_combining;
            i2 = i;
          } else {
            if (i1 != i)
              i1 = i;
            else {
              i = i2;
              if (last_wc == viet_comp_table_data[i].base)
                break;
              goto not_combining;
            }
          }
        }
        last_wc = viet_comp_table_data[i].composed;
        /* Output the combined character. */
        conv->istate = 0;
        *pwc = (ucs4_t) last_wc;
        return 1;
      }
    }
  not_combining:
    /* Output the buffered character. */
    conv->istate = 0;
    *pwc = (ucs4_t) last_wc;
    return 0; /* Don't advance the input pointer. */
  }
  if (wc >= 0x0041 && wc <= 0x01b0
      && ((cp1258_comp_bases[(wc - 0x0040) >> 5] >> (wc & 0x1f)) & 1)) {
    /* wc is a possible match in viet_comp_table_data. Buffer it. */
    conv->istate = wc;
    return RET_TOOFEW(1);
  } else {
    /* Output wc immediately. */
    *pwc = (ucs4_t) wc;
    return 1;
  }
}