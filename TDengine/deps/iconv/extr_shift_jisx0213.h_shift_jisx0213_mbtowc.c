#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ucs4_t ;
typedef  TYPE_1__* conv_t ;
struct TYPE_3__ {int istate; } ;

/* Variables and functions */
 int RET_ILSEQ ; 
 int RET_TOOFEW (int /*<<< orphan*/ ) ; 
 int jisx0213_to_ucs4 (int,unsigned char) ; 
 int** jisx0213_to_ucs_combining ; 

__attribute__((used)) static int
shift_jisx0213_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  ucs4_t last_wc = conv->istate;
  if (last_wc) {
    /* Output the buffered character. */
    conv->istate = 0;
    *pwc = last_wc;
    return 0; /* Don't advance the input pointer. */
  } else {
    unsigned char c = *s;
    if (c < 0x80) {
      /* Plain ISO646-JP character. */
      if (c == 0x5c)
        *pwc = (ucs4_t) 0x00a5;
      else if (c == 0x7e)
        *pwc = (ucs4_t) 0x203e;
      else
        *pwc = (ucs4_t) c;
      return 1;
    } else if (c >= 0xa1 && c <= 0xdf) {
      *pwc = c + 0xfec0;
      return 1;
    } else {
      if ((c >= 0x81 && c <= 0x9f) || (c >= 0xe0 && c <= 0xfc)) {
        /* Two byte character. */
        if (n >= 2) {
          unsigned char c2 = s[1];
          if ((c2 >= 0x40 && c2 <= 0x7e) || (c2 >= 0x80 && c2 <= 0xfc)) {
            unsigned int c1;
            ucs4_t wc;
            /* Convert to row and column. */
            if (c < 0xe0)
              c -= 0x81;
            else
              c -= 0xc1;
            if (c2 < 0x80)
              c2 -= 0x40;
            else
              c2 -= 0x41;
            /* Now 0 <= c <= 0x3b, 0 <= c2 <= 0xbb. */
            c1 = 2 * c;
            if (c2 >= 0x5e)
              c2 -= 0x5e, c1++;
            c2 += 0x21;
            if (c1 >= 0x5e) {
              /* Handling of JISX 0213 plane 2 rows. */
              if (c1 >= 0x67)
                c1 += 230;
              else if (c1 >= 0x63 || c1 == 0x5f)
                c1 += 168;
              else
                c1 += 162;
            }
            wc = jisx0213_to_ucs4(0x121+c1,c2);
            if (wc) {
              if (wc < 0x80) {
                /* It's a combining character. */
                ucs4_t wc1 = jisx0213_to_ucs_combining[wc - 1][0];
                ucs4_t wc2 = jisx0213_to_ucs_combining[wc - 1][1];
                /* We cannot output two Unicode characters at once. So,
                   output the first character and buffer the second one. */
                *pwc = wc1;
                conv->istate = wc2;
              } else
                *pwc = wc;
              return 2;
            }
          }
        } else
          return RET_TOOFEW(0);
      }
      return RET_ILSEQ;
    }
  }
}