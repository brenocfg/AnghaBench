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
struct uc_to_mb_fallback_locals {scalar_t__ l_errno; size_t l_outbytesleft; size_t l_outbuf; } ;

/* Variables and functions */
 scalar_t__ E2BIG ; 
 int /*<<< orphan*/  memcpy (size_t,char const*,size_t) ; 

__attribute__((used)) static void uc_to_mb_write_replacement (const char *buf, size_t buflen,
                                        void* callback_arg)
{
  struct uc_to_mb_fallback_locals * plocals =
    (struct uc_to_mb_fallback_locals *) callback_arg;
  /* Do nothing if already encountered an error in a previous call. */
  if (plocals->l_errno == 0) {
    /* Attempt to copy the passed buffer to the output buffer. */
    if (plocals->l_outbytesleft < buflen)
      plocals->l_errno = E2BIG;
    else {
      memcpy(plocals->l_outbuf, buf, buflen);
      plocals->l_outbuf += buflen;
      plocals->l_outbytesleft -= buflen;
    }
  }
}