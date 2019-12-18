#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ucs4_t ;
typedef  int /*<<< orphan*/  conv_t ;

/* Variables and functions */
 unsigned char FILL ; 
 unsigned char NONE ; 
 int RET_ILSEQ ; 
 int RET_TOOFEW (int /*<<< orphan*/ ) ; 
 int fill ; 
 int* jamo_final_index ; 
 unsigned char* jamo_final_notinitial ; 
 unsigned char* jamo_initial ; 
 int* jamo_initial_index ; 
 unsigned char* jamo_medial ; 
 int* jamo_medial_index ; 

__attribute__((used)) static int
johab_hangul_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  unsigned char c1 = s[0];
  if ((c1 >= 0x84 && c1 <= 0xd3)) {
    if (n >= 2) {
      unsigned char c2 = s[1];
      if ((c2 >= 0x41 && c2 < 0x7f) || (c2 >= 0x81 && c2 < 0xff)) {
        unsigned int johab = (c1 << 8) | c2;
        unsigned int bitspart1 = (johab >> 10) & 31;
        unsigned int bitspart2 = (johab >> 5) & 31;
        unsigned int bitspart3 = johab & 31;
        int index1 = jamo_initial_index[bitspart1];
        int index2 = jamo_medial_index[bitspart2];
        int index3 = jamo_final_index[bitspart3];
        /* Exclude "none" values. */
        if (index1 >= 0 && index2 >= 0 && index3 >= 0) {
          /* Deal with "fill" values in initial or medial position. */
          if (index1 == fill) {
            if (index2 == fill) {
              unsigned char jamo3 = jamo_final_notinitial[bitspart3];
              if (jamo3 != NONE) {
                *pwc = (ucs4_t) 0x3130 + jamo3;
                return 2;
              }
            } else if (index3 == fill) {
              unsigned char jamo2 = jamo_medial[bitspart2];
              if (jamo2 != NONE && jamo2 != FILL) {
                *pwc = (ucs4_t) 0x3130 + jamo2;
                return 2;
              }
            }
            /* Syllables composed only of medial and final don't exist. */
          } else if (index2 == fill) {
            if (index3 == fill) {
              unsigned char jamo1 = jamo_initial[bitspart1];
              if (jamo1 != NONE && jamo1 != FILL) {
                *pwc = (ucs4_t) 0x3130 + jamo1;
                return 2;
              }
            }
            /* Syllables composed only of initial and final don't exist. */
          } else {
             /* index1 and index2 are not fill, but index3 may be fill. */
             /* Nothing more to exclude. All 11172 code points are valid. */
             *pwc = 0xac00 + ((index1 - 1) * 21 + (index2 - 1)) * 28 + index3;
             return 2;
          }
        }
      }
      return RET_ILSEQ;
    }
    return RET_TOOFEW(0);
  }
  return RET_ILSEQ;
}