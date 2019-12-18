#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ucs4_t ;
struct uc_to_mb_fallback_locals {unsigned char* l_outbuf; size_t l_outbytesleft; scalar_t__ l_errno; } ;
struct mb_to_uc_fallback_locals {scalar_t__ l_errno; unsigned char* l_outbuf; size_t l_outbytesleft; TYPE_4__* l_cd; } ;
typedef  TYPE_4__* conv_t ;
struct TYPE_10__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* uc_hook ) (int,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int (* xxx_wctomb ) (TYPE_4__*,unsigned char*,int,size_t) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* uc_to_mb_fallback ) (int,int /*<<< orphan*/ ,struct uc_to_mb_fallback_locals*,int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {TYPE_3__ hooks; TYPE_2__ ofuncs; TYPE_1__ fallbacks; scalar_t__ discard_ilseq; scalar_t__ transliterate; } ;

/* Variables and functions */
 void* E2BIG ; 
 scalar_t__ EILSEQ ; 
 int RET_ILUNI ; 
 int /*<<< orphan*/  abort () ; 
 int stub1 (TYPE_4__*,unsigned char*,int,size_t) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ,struct uc_to_mb_fallback_locals*,int /*<<< orphan*/ ) ; 
 int stub3 (TYPE_4__*,unsigned char*,int,size_t) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uc_to_mb_write_replacement ; 
 int unicode_transliterate (TYPE_4__*,int,unsigned char*,size_t) ; 

__attribute__((used)) static void mb_to_uc_write_replacement (const unsigned int *buf, size_t buflen,
                                        void* callback_arg)
{
  struct mb_to_uc_fallback_locals * plocals =
    (struct mb_to_uc_fallback_locals *) callback_arg;
  /* Do nothing if already encountered an error in a previous call. */
  if (plocals->l_errno == 0) {
    /* Attempt to convert the passed buffer to the target encoding. */
    conv_t cd = plocals->l_cd;
    unsigned char* outptr = plocals->l_outbuf;
    size_t outleft = plocals->l_outbytesleft;
    for (; buflen > 0; buf++, buflen--) {
      ucs4_t wc = *buf;
      int outcount;
      if (outleft == 0) {
        plocals->l_errno = E2BIG;
        break;
      }
      outcount = cd->ofuncs.xxx_wctomb(cd,outptr,wc,outleft);
      if (outcount != RET_ILUNI)
        goto outcount_ok;
      /* Handle Unicode tag characters (range U+E0000..U+E007F). */
      if ((wc >> 7) == (0xe0000 >> 7))
        goto outcount_zero;
      /* Try transliteration. */
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
          plocals->l_errno = locals.l_errno;
          break;
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
      plocals->l_errno = EILSEQ;
      break;
    outcount_ok:
      if (outcount < 0) {
        plocals->l_errno = E2BIG;
        break;
      }
      #ifndef LIBICONV_PLUG
      if (cd->hooks.uc_hook)
        (*cd->hooks.uc_hook)(wc, cd->hooks.data);
      #endif
      if (!(outcount <= outleft)) abort();
      outptr += outcount; outleft -= outcount;
    outcount_zero: ;
    }
    plocals->l_outbuf = outptr;
    plocals->l_outbytesleft = outleft;
  }
}