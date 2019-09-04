#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int ucs4_t ;
struct uc_to_mb_fallback_locals {unsigned char* l_outbuf; size_t l_outbytesleft; scalar_t__ l_errno; } ;
struct mb_to_uc_fallback_locals {unsigned char* l_outbuf; size_t l_outbytesleft; scalar_t__ l_errno; TYPE_5__* l_cd; } ;
typedef  void* state_t ;
typedef  int /*<<< orphan*/  iconv_t ;
typedef  TYPE_5__* conv_t ;
struct TYPE_13__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* uc_hook ) (int,int /*<<< orphan*/ ) ;} ;
struct TYPE_12__ {int (* xxx_wctomb ) (TYPE_5__*,unsigned char*,int,size_t) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* uc_to_mb_fallback ) (int,int /*<<< orphan*/ ,struct uc_to_mb_fallback_locals*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* mb_to_uc_fallback ) (char const*,unsigned int,int /*<<< orphan*/ ,struct mb_to_uc_fallback_locals*,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {int (* xxx_mbtowc ) (TYPE_5__*,int*,unsigned char const*,size_t) ;} ;
struct TYPE_14__ {int iindex; TYPE_4__ hooks; void* istate; TYPE_3__ ofuncs; TYPE_2__ fallbacks; scalar_t__ discard_ilseq; scalar_t__ transliterate; TYPE_1__ ifuncs; } ;

/* Variables and functions */
 int DECODE_SHIFT_ILSEQ (int) ; 
 int DECODE_TOOFEW (int) ; 
 scalar_t__ E2BIG ; 
 scalar_t__ EILSEQ ; 
 scalar_t__ EINVAL ; 
 int RET_ILSEQ ; 
 int RET_ILUNI ; 
 int RET_TOOFEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
#define  ei_ucs2 143 
#define  ei_ucs2be 142 
#define  ei_ucs2internal 141 
#define  ei_ucs2le 140 
#define  ei_ucs2swapped 139 
#define  ei_ucs4 138 
#define  ei_ucs4be 137 
#define  ei_ucs4internal 136 
#define  ei_ucs4le 135 
#define  ei_ucs4swapped 134 
#define  ei_utf16 133 
#define  ei_utf16be 132 
#define  ei_utf16le 131 
#define  ei_utf32 130 
#define  ei_utf32be 129 
#define  ei_utf32le 128 
 scalar_t__ errno ; 
 int /*<<< orphan*/  mb_to_uc_write_replacement ; 
 int stub1 (TYPE_5__*,int*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  stub2 (char const*,unsigned int,int /*<<< orphan*/ ,struct mb_to_uc_fallback_locals*,int /*<<< orphan*/ ) ; 
 int stub3 (TYPE_5__*,unsigned char*,int,size_t) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ ,struct uc_to_mb_fallback_locals*,int /*<<< orphan*/ ) ; 
 int stub5 (TYPE_5__*,unsigned char*,int,size_t) ; 
 int /*<<< orphan*/  stub6 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uc_to_mb_write_replacement ; 
 int unicode_transliterate (TYPE_5__*,int,unsigned char*,size_t) ; 

__attribute__((used)) static size_t unicode_loop_convert (iconv_t icd,
                                    const char* * inbuf, size_t *inbytesleft,
                                    char* * outbuf, size_t *outbytesleft)
{
  conv_t cd = (conv_t) icd;
  size_t result = 0;
  const unsigned char* inptr = (const unsigned char*) *inbuf;
  size_t inleft = *inbytesleft;
  unsigned char* outptr = (unsigned char*) *outbuf;
  size_t outleft = *outbytesleft;
  while (inleft > 0) {
    state_t last_istate = cd->istate;
    ucs4_t wc;
    int incount;
    int outcount;
    incount = cd->ifuncs.xxx_mbtowc(cd,&wc,inptr,inleft);
    if (incount < 0) {
      if ((unsigned int)(-1-incount) % 2 == (unsigned int)(-1-RET_ILSEQ) % 2) {
        /* Case 1: invalid input, possibly after a shift sequence */
        incount = DECODE_SHIFT_ILSEQ(incount);
        if (cd->discard_ilseq) {
          switch (cd->iindex) {
            case ei_ucs4: case ei_ucs4be: case ei_ucs4le:
            case ei_utf32: case ei_utf32be: case ei_utf32le:
            case ei_ucs4internal: case ei_ucs4swapped:
              incount += 4; break;
            case ei_ucs2: case ei_ucs2be: case ei_ucs2le:
            case ei_utf16: case ei_utf16be: case ei_utf16le:
            case ei_ucs2internal: case ei_ucs2swapped:
              incount += 2; break;
            default:
              incount += 1; break;
          }
          goto outcount_zero;
        }
        #ifndef LIBICONV_PLUG
        else if (cd->fallbacks.mb_to_uc_fallback != NULL) {
          unsigned int incount2;
          struct mb_to_uc_fallback_locals locals;
          switch (cd->iindex) {
            case ei_ucs4: case ei_ucs4be: case ei_ucs4le:
            case ei_utf32: case ei_utf32be: case ei_utf32le:
            case ei_ucs4internal: case ei_ucs4swapped:
              incount2 = 4; break;
            case ei_ucs2: case ei_ucs2be: case ei_ucs2le:
            case ei_utf16: case ei_utf16be: case ei_utf16le:
            case ei_ucs2internal: case ei_ucs2swapped:
              incount2 = 2; break;
            default:
              incount2 = 1; break;
          }
          locals.l_cd = cd;
          locals.l_outbuf = outptr;
          locals.l_outbytesleft = outleft;
          locals.l_errno = 0;
          cd->fallbacks.mb_to_uc_fallback((const char*)inptr+incount, incount2,
                                          mb_to_uc_write_replacement,
                                          &locals,
                                          cd->fallbacks.data);
          if (locals.l_errno != 0) {
            inptr += incount; inleft -= incount;
            errno = locals.l_errno;
            result = -1;
            break;
          }
          incount += incount2;
          outptr = locals.l_outbuf;
          outleft = locals.l_outbytesleft;
          result += 1;
          goto outcount_zero;
        }
        #endif
        inptr += incount; inleft -= incount;
        errno = EILSEQ;
        result = -1;
        break;
      }
      if (incount == RET_TOOFEW(0)) {
        /* Case 2: not enough bytes available to detect anything */
        errno = EINVAL;
        result = -1;
        break;
      }
      /* Case 3: k bytes read, but only a shift sequence */
      incount = DECODE_TOOFEW(incount);
    } else {
      /* Case 4: k bytes read, making up a wide character */
      if (outleft == 0) {
        cd->istate = last_istate;
        errno = E2BIG;
        result = -1;
        break;
      }
      outcount = cd->ofuncs.xxx_wctomb(cd,outptr,wc,outleft);
      if (outcount != RET_ILUNI)
        goto outcount_ok;
      /* Handle Unicode tag characters (range U+E0000..U+E007F). */
      if ((wc >> 7) == (0xe0000 >> 7))
        goto outcount_zero;
      /* Try transliteration. */
      result++;
      if (cd->transliterate) {
        outcount = unicode_transliterate(cd,wc,outptr,outleft);
        if (outcount != RET_ILUNI)
          goto outcount_ok;
      }
      if (cd->discard_ilseq) {
        outcount = 0;
        goto outcount_ok;
      }
      #ifndef LIBICONV_PLUG
      else if (cd->fallbacks.uc_to_mb_fallback != NULL) {
        struct uc_to_mb_fallback_locals locals;
        locals.l_outbuf = outptr;
        locals.l_outbytesleft = outleft;
        locals.l_errno = 0;
        cd->fallbacks.uc_to_mb_fallback(wc,
                                        uc_to_mb_write_replacement,
                                        &locals,
                                        cd->fallbacks.data);
        if (locals.l_errno != 0) {
          cd->istate = last_istate;
          errno = locals.l_errno;
          return -1;
        }
        outptr = locals.l_outbuf;
        outleft = locals.l_outbytesleft;
        outcount = 0;
        goto outcount_ok;
      }
      #endif
      outcount = cd->ofuncs.xxx_wctomb(cd,outptr,0xFFFD,outleft);
      if (outcount != RET_ILUNI)
        goto outcount_ok;
      cd->istate = last_istate;
      errno = EILSEQ;
      result = -1;
      break;
    outcount_ok:
      if (outcount < 0) {
        cd->istate = last_istate;
        errno = E2BIG;
        result = -1;
        break;
      }
      #ifndef LIBICONV_PLUG
      if (cd->hooks.uc_hook)
        (*cd->hooks.uc_hook)(wc, cd->hooks.data);
      #endif
      if (!(outcount <= outleft)) abort();
      outptr += outcount; outleft -= outcount;
    }
  outcount_zero:
    if (!(incount <= inleft)) abort();
    inptr += incount; inleft -= incount;
  }
  *inbuf = (const char*) inptr;
  *inbytesleft = inleft;
  *outbuf = (char*) outptr;
  *outbytesleft = outleft;
  return result;
}