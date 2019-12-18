#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iconv_hooks {int /*<<< orphan*/ * data; int /*<<< orphan*/ * wc_hook; int /*<<< orphan*/ * uc_hook; } ;
struct iconv_fallbacks {int /*<<< orphan*/ * data; int /*<<< orphan*/ * wc_to_mb_fallback; int /*<<< orphan*/ * mb_to_wc_fallback; int /*<<< orphan*/ * uc_to_mb_fallback; int /*<<< orphan*/ * mb_to_uc_fallback; } ;
typedef  int /*<<< orphan*/  iconv_t ;
typedef  TYPE_2__* conv_t ;
struct TYPE_3__ {int /*<<< orphan*/  loop_convert; } ;
struct TYPE_4__ {int transliterate; int discard_ilseq; struct iconv_fallbacks fallbacks; struct iconv_hooks hooks; TYPE_1__ lfuncs; int /*<<< orphan*/  oindex; int /*<<< orphan*/  iindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  ICONV_GET_DISCARD_ILSEQ 134 
#define  ICONV_GET_TRANSLITERATE 133 
#define  ICONV_SET_DISCARD_ILSEQ 132 
#define  ICONV_SET_FALLBACKS 131 
#define  ICONV_SET_HOOKS 130 
#define  ICONV_SET_TRANSLITERATE 129 
#define  ICONV_TRIVIALP 128 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  unicode_loop_convert ; 
 int /*<<< orphan*/  wchar_id_loop_convert ; 

int iconvctl (iconv_t icd, int request, void* argument)
{
  conv_t cd = (conv_t) icd;
  switch (request) {
    case ICONV_TRIVIALP:
      *(int *)argument =
        ((cd->lfuncs.loop_convert == unicode_loop_convert
          && cd->iindex == cd->oindex)
         || cd->lfuncs.loop_convert == wchar_id_loop_convert
         ? 1 : 0);
      return 0;
    case ICONV_GET_TRANSLITERATE:
      *(int *)argument = cd->transliterate;
      return 0;
    case ICONV_SET_TRANSLITERATE:
      cd->transliterate = (*(const int *)argument ? 1 : 0);
      return 0;
    case ICONV_GET_DISCARD_ILSEQ:
      *(int *)argument = cd->discard_ilseq;
      return 0;
    case ICONV_SET_DISCARD_ILSEQ:
      cd->discard_ilseq = (*(const int *)argument ? 1 : 0);
      return 0;
    case ICONV_SET_HOOKS:
      if (argument != NULL) {
        cd->hooks = *(const struct iconv_hooks *)argument;
      } else {
        cd->hooks.uc_hook = NULL;
        cd->hooks.wc_hook = NULL;
        cd->hooks.data = NULL;
      }
      return 0;
    case ICONV_SET_FALLBACKS:
      if (argument != NULL) {
        cd->fallbacks = *(const struct iconv_fallbacks *)argument;
      } else {
        cd->fallbacks.mb_to_uc_fallback = NULL;
        cd->fallbacks.uc_to_mb_fallback = NULL;
        cd->fallbacks.mb_to_wc_fallback = NULL;
        cd->fallbacks.wc_to_mb_fallback = NULL;
        cd->fallbacks.data = NULL;
      }
      return 0;
    default:
      errno = EINVAL;
      return -1;
  }
}