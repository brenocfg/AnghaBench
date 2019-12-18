#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
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
 unsigned short* cp1255_2uni ; 
 TYPE_4__* cp1255_comp_table ; 
 TYPE_3__* cp1255_comp_table_data ; 

__attribute__((used)) static int
cp1255_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  unsigned char c = *s;
  unsigned short wc;
  unsigned short last_wc;
  if (c < 0x80) {
    wc = c;
  } else {
    wc = cp1255_2uni[c-0x80];
    if (wc == 0xfffd)
      return RET_ILSEQ;
  }
  last_wc = conv->istate;
  if (last_wc) {
    if (wc >= 0x05b0 && wc < 0x05c5) {
      /* See whether last_wc and wc can be combined. */
      unsigned int k;
      unsigned int i1, i2;
      switch (wc) {
        case 0x05b4: k = 0; break;
        case 0x05b7: k = 1; break;
        case 0x05b8: k = 2; break;
        case 0x05b9: k = 3; break;
        case 0x05bc: k = 4; break;
        case 0x05bf: k = 5; break;
        case 0x05c1: k = 6; break;
        case 0x05c2: k = 7; break;
        default: goto not_combining;
      }
      i1 = cp1255_comp_table[k].idx;
      i2 = i1 + cp1255_comp_table[k].len-1;
      if (last_wc >= cp1255_comp_table_data[i1].base
          && last_wc <= cp1255_comp_table_data[i2].base) {
        unsigned int i;
        for (;;) {
          i = (i1+i2)>>1;
          if (last_wc == cp1255_comp_table_data[i].base)
            break;
          if (last_wc < cp1255_comp_table_data[i].base) {
            if (i1 == i)
              goto not_combining;
            i2 = i;
          } else {
            if (i1 != i)
              i1 = i;
            else {
              i = i2;
              if (last_wc == cp1255_comp_table_data[i].base)
                break;
              goto not_combining;
            }
          }
        }
        last_wc = cp1255_comp_table_data[i].composed;
        if (last_wc == 0xfb2a || last_wc == 0xfb2b || last_wc == 0xfb49) {
          /* Buffer the combined character. */
          conv->istate = last_wc;
          return RET_TOOFEW(1);
        } else {
          /* Output the combined character. */
          conv->istate = 0;
          *pwc = (ucs4_t) last_wc;
          return 1;
        }
      }
    }
  not_combining:
    /* Output the buffered character. */
    conv->istate = 0;
    *pwc = (ucs4_t) last_wc;
    return 0; /* Don't advance the input pointer. */
  }
  if ((wc >= 0x05d0 && wc <= 0x05ea && ((0x07db5f7f >> (wc - 0x05d0)) & 1))
      || wc == 0x05f2) {
    /* wc is a possible match in cp1255_comp_table_data. Buffer it. */
    conv->istate = wc;
    return RET_TOOFEW(1);
  } else {
    /* Output wc immediately. */
    *pwc = (ucs4_t) wc;
    return 1;
  }
}