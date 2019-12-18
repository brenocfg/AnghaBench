#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cxgbi_sock {int /*<<< orphan*/  atid; TYPE_1__* cdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  lldev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTPF_HAS_ATID ; 
 int /*<<< orphan*/  cxgb3_free_atid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_sock_clear_flag (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ cxgbi_sock_flag (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_sock_put (struct cxgbi_sock*) ; 

__attribute__((used)) static inline void free_atid(struct cxgbi_sock *csk)
{
	if (cxgbi_sock_flag(csk, CTPF_HAS_ATID)) {
		cxgb3_free_atid(csk->cdev->lldev, csk->atid);
		cxgbi_sock_clear_flag(csk, CTPF_HAS_ATID);
		cxgbi_sock_put(csk);
	}
}