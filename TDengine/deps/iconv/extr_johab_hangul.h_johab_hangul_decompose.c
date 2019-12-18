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
typedef  int /*<<< orphan*/  ucs4_t ;
typedef  int /*<<< orphan*/  conv_t ;

/* Variables and functions */
 unsigned char FILL ; 
 unsigned char NONE ; 
 int RET_ILUNI ; 
 int /*<<< orphan*/  abort () ; 
 unsigned char* jamo_final ; 
 unsigned char* jamo_initial ; 
 unsigned char* jamo_medial ; 
 int johab_hangul_wctomb (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int johab_hangul_decompose (conv_t conv, ucs4_t* r, ucs4_t wc)
{
  unsigned char buf[2];
  int ret = johab_hangul_wctomb(conv,buf,wc,2);
  if (ret != RET_ILUNI) {
    unsigned int hangul = (buf[0] << 8) | buf[1];
    unsigned char jamo1 = jamo_initial[(hangul >> 10) & 31];
    unsigned char jamo2 = jamo_medial[(hangul >> 5) & 31];
    unsigned char jamo3 = jamo_final[hangul & 31];
    if ((hangul >> 15) != 1) abort();
    if (jamo1 != NONE && jamo2 != NONE && jamo3 != NONE) {
      /* They are not all three == FILL because that would correspond to
         johab = 0x8441, which doesn't exist. */
      ucs4_t* p = r;
      if (jamo1 != FILL)
        *p++ = 0x3130 + jamo1;
      if (jamo2 != FILL)
        *p++ = 0x3130 + jamo2;
      if (jamo3 != FILL)
        *p++ = 0x3130 + jamo3;
      return p-r;
    }
  }
  return RET_ILUNI;
}