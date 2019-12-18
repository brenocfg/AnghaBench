#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int ucs4_t ;
typedef  void* state_t ;
typedef  TYPE_2__* conv_t ;
struct TYPE_9__ {int (* xxx_wctomb ) (TYPE_2__*,unsigned char*,int,size_t) ;} ;
struct TYPE_10__ {int oflags; void* ostate; TYPE_1__ ofuncs; } ;

/* Variables and functions */
 int HAVE_ACCENTS ; 
 int HAVE_HANGUL_JAMO ; 
 int HAVE_QUOTATION_MARKS ; 
 int RET_ILUNI ; 
 int RET_TOOSMALL ; 
 int /*<<< orphan*/  abort () ; 
 unsigned short* cjk_variants ; 
 int* cjk_variants_indx ; 
 int johab_hangul_decompose (TYPE_2__*,int*,int) ; 
 int stub1 (TYPE_2__*,unsigned char*,int,size_t) ; 
 int stub2 (TYPE_2__*,unsigned char*,int,size_t) ; 
 int stub3 (TYPE_2__*,unsigned char*,int,size_t) ; 
 int stub4 (TYPE_2__*,unsigned char*,unsigned int const,size_t) ; 
 unsigned int* translit_data ; 
 int translit_index (int) ; 

__attribute__((used)) static int unicode_transliterate (conv_t cd, ucs4_t wc,
                                  unsigned char* outptr, size_t outleft)
{
  if (cd->oflags & HAVE_HANGUL_JAMO) {
    /* Decompose Hangul into Jamo. Use double-width Jamo (contained
       in all Korean encodings and ISO-2022-JP-2), not half-width Jamo
       (contained in Unicode only). */
    ucs4_t buf[3];
    int ret = johab_hangul_decompose(cd,buf,wc);
    if (ret != RET_ILUNI) {
      /* we know 1 <= ret <= 3 */
      state_t backup_state = cd->ostate;
      unsigned char* backup_outptr = outptr;
      size_t backup_outleft = outleft;
      int i, sub_outcount;
      for (i = 0; i < ret; i++) {
        if (outleft == 0) {
          sub_outcount = RET_TOOSMALL;
          goto johab_hangul_failed;
        }
        sub_outcount = cd->ofuncs.xxx_wctomb(cd,outptr,buf[i],outleft);
        if (sub_outcount <= RET_ILUNI)
          goto johab_hangul_failed;
        if (!(sub_outcount <= outleft)) abort();
        outptr += sub_outcount; outleft -= sub_outcount;
      }
      return outptr-backup_outptr;
    johab_hangul_failed:
      cd->ostate = backup_state;
      outptr = backup_outptr;
      outleft = backup_outleft;
      if (sub_outcount != RET_ILUNI)
        return RET_TOOSMALL;
    }
  }
  {
    /* Try to use a variant, but postfix it with
       U+303E IDEOGRAPHIC VARIATION INDICATOR
       (cf. Ken Lunde's "CJKV information processing", p. 188). */
    int indx = -1;
    if (wc == 0x3006)
      indx = 0;
    else if (wc == 0x30f6)
      indx = 1;
    else if (wc >= 0x4e00 && wc < 0xa000)
      indx = cjk_variants_indx[wc-0x4e00];
    if (indx >= 0) {
      for (;; indx++) {
        ucs4_t buf[2];
        unsigned short variant = cjk_variants[indx];
        unsigned short last = variant & 0x8000;
        variant &= 0x7fff;
        variant += 0x3000;
        buf[0] = variant; buf[1] = 0x303e;
        {
          state_t backup_state = cd->ostate;
          unsigned char* backup_outptr = outptr;
          size_t backup_outleft = outleft;
          int i, sub_outcount;
          for (i = 0; i < 2; i++) {
            if (outleft == 0) {
              sub_outcount = RET_TOOSMALL;
              goto variant_failed;
            }
            sub_outcount = cd->ofuncs.xxx_wctomb(cd,outptr,buf[i],outleft);
            if (sub_outcount <= RET_ILUNI)
              goto variant_failed;
            if (!(sub_outcount <= outleft)) abort();
            outptr += sub_outcount; outleft -= sub_outcount;
          }
          return outptr-backup_outptr;
        variant_failed:
          cd->ostate = backup_state;
          outptr = backup_outptr;
          outleft = backup_outleft;
          if (sub_outcount != RET_ILUNI)
            return RET_TOOSMALL;
        }
        if (last)
          break;
      }
    }
  }
  if (wc >= 0x2018 && wc <= 0x201a) {
    /* Special case for quotation marks 0x2018, 0x2019, 0x201a */
    ucs4_t substitute =
      (cd->oflags & HAVE_QUOTATION_MARKS
       ? (wc == 0x201a ? 0x2018 : wc)
       : (cd->oflags & HAVE_ACCENTS
          ? (wc==0x2019 ? 0x00b4 : 0x0060) /* use accents */
          : 0x0027 /* use apostrophe */
      )  );
    int outcount = cd->ofuncs.xxx_wctomb(cd,outptr,substitute,outleft);
    if (outcount != RET_ILUNI)
      return outcount;
  }
  {
    /* Use the transliteration table. */
    int indx = translit_index(wc);
    if (indx >= 0) {
      const unsigned int * cp = &translit_data[indx];
      unsigned int num = *cp++;
      state_t backup_state = cd->ostate;
      unsigned char* backup_outptr = outptr;
      size_t backup_outleft = outleft;
      unsigned int i;
      int sub_outcount;
      for (i = 0; i < num; i++) {
        if (outleft == 0) {
          sub_outcount = RET_TOOSMALL;
          goto translit_failed;
        }
        sub_outcount = cd->ofuncs.xxx_wctomb(cd,outptr,cp[i],outleft);
        if (sub_outcount == RET_ILUNI)
          /* Recursive transliteration. */
          sub_outcount = unicode_transliterate(cd,cp[i],outptr,outleft);
        if (sub_outcount <= RET_ILUNI)
          goto translit_failed;
        if (!(sub_outcount <= outleft)) abort();
        outptr += sub_outcount; outleft -= sub_outcount;
      }
      return outptr-backup_outptr;
    translit_failed:
      cd->ostate = backup_state;
      outptr = backup_outptr;
      outleft = backup_outleft;
      if (sub_outcount != RET_ILUNI)
        return RET_TOOSMALL;
    }
  }
  return RET_ILUNI;
}