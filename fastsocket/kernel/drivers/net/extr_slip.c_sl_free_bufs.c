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
struct slip {int /*<<< orphan*/  slcomp; int /*<<< orphan*/  cbuff; int /*<<< orphan*/  xbuff; int /*<<< orphan*/  rbuff; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slhc_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sl_free_bufs(struct slip *sl)
{
	/* Free all SLIP frame buffers. */
	kfree(xchg(&sl->rbuff, NULL));
	kfree(xchg(&sl->xbuff, NULL));
#ifdef SL_INCLUDE_CSLIP
	kfree(xchg(&sl->cbuff, NULL));
	slhc_free(xchg(&sl->slcomp, NULL));
#endif
}