#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mbuf {int dummy; } ;
struct TYPE_4__ {scalar_t__ mca_contents_size; } ;
typedef  TYPE_1__ mcache_audit_t ;

/* Variables and functions */
 scalar_t__ AUDIT_CONTENTS_SIZE ; 
 int /*<<< orphan*/  MCA_SAVED_MBUF_PTR (TYPE_1__*) ; 
 int /*<<< orphan*/  MCA_SAVED_MBUF_SIZE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  _MCHECK (struct mbuf*) ; 
 int /*<<< orphan*/  bcopy (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mcl_audit_save_mbuf(struct mbuf *m, mcache_audit_t *mca)
{
	VERIFY(mca->mca_contents_size == AUDIT_CONTENTS_SIZE);
	_MCHECK(m);
	bcopy(m, MCA_SAVED_MBUF_PTR(mca), MCA_SAVED_MBUF_SIZE);
}