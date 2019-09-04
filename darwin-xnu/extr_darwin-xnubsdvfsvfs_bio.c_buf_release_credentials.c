#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* buf_t ;
struct TYPE_3__ {int /*<<< orphan*/  b_wcred; int /*<<< orphan*/  b_rcred; } ;

/* Variables and functions */
 scalar_t__ IS_VALID_CRED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline__ void
buf_release_credentials(buf_t bp)
{
	if (IS_VALID_CRED(bp->b_rcred)) {
		kauth_cred_unref(&bp->b_rcred);
	}
	if (IS_VALID_CRED(bp->b_wcred)) {
		kauth_cred_unref(&bp->b_wcred);
	}
}