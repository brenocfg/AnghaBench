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
typedef  int /*<<< orphan*/  wchar_t ;
struct mb_to_wc_fallback_locals {scalar_t__ l_errno; int l_outbytesleft; scalar_t__ l_outbuf; } ;

/* Variables and functions */
 scalar_t__ E2BIG ; 

__attribute__((used)) static void mb_to_wc_write_replacement (const wchar_t *buf, size_t buflen,
                                        void* callback_arg)
{
  struct mb_to_wc_fallback_locals * plocals =
    (struct mb_to_wc_fallback_locals *) callback_arg;
  /* Do nothing if already encountered an error in a previous call. */
  if (plocals->l_errno == 0) {
    /* Attempt to copy the passed buffer to the output buffer. */
    if (plocals->l_outbytesleft < sizeof(wchar_t)*buflen)
      plocals->l_errno = E2BIG;
    else {
      for (; buflen > 0; buf++, buflen--) {
        *(wchar_t*) plocals->l_outbuf = *buf;
        plocals->l_outbuf += sizeof(wchar_t);
        plocals->l_outbytesleft -= sizeof(wchar_t);
      }
    }
  }
}