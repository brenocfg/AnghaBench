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
struct cfi_buf {scalar_t__ cfi_pending_first; scalar_t__ cfi_pending_last; scalar_t__ cfi_pending_mbcnt; int /*<<< orphan*/  cfi_inject_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFIL_QUEUE_VERIFY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY (int) ; 

__attribute__((used)) static void
cfil_info_buf_verify(struct cfi_buf *cfi_buf)
{
	CFIL_QUEUE_VERIFY(&cfi_buf->cfi_inject_q);

	VERIFY(cfi_buf->cfi_pending_first <= cfi_buf->cfi_pending_last);
	VERIFY(cfi_buf->cfi_pending_mbcnt >= 0);
}