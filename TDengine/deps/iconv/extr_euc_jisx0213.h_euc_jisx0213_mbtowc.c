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
euc_jisx0213_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
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
      /* Plain ASCII character. */
      *pwc = (ucs4_t) c;
      return 1;
    } else {
      if ((c >= 0xa1 && c <= 0xfe) || c == 0x8e || c == 0x8f) {
        /* Two or three byte character. */
        if (n >= 2) {
          unsigned char c2 = s[1];
          if (c2 >= 0xa1 && c2 <= 0xfe) {
            if (c == 0x8e) {
              /* Half-width katakana. */
              if (c2 <= 0xdf) {
                *pwc = c2 + 0xfec0;
                return 2;
              }
            } else {
              ucs4_t wc;
              if (c == 0x8f) {
                /* JISX 0213 plane 2. */
                if (n >= 3) {
                  unsigned char c3 = s[2];
                  wc = jisx0213_to_ucs4(0x200-0x80+c2,c3^0x80);
                } else
                  return RET_TOOFEW(0);
              } else {
                /* JISX 0213 plane 1. */
                wc = jisx0213_to_ucs4(0x100-0x80+c,c2^0x80);
              }
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
                return (c == 0x8f ? 3 : 2);
              }
            }
          }
        } else
          return RET_TOOFEW(0);
      }
      return RET_ILSEQ;
    }
  }
}