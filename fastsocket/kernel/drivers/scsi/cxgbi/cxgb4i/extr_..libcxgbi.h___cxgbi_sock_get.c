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
struct TYPE_2__ {int /*<<< orphan*/  refcount; } ;
struct cxgbi_sock {TYPE_1__ refcnt; } ;

/* Variables and functions */
 int CXGBI_DBG_SOCK ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_get (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug (int,char*,char const*,struct cxgbi_sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __cxgbi_sock_get(const char *fn, struct cxgbi_sock *csk)
{
	log_debug(1 << CXGBI_DBG_SOCK,
		"%s, get csk 0x%p, ref %u+1.\n",
		fn, csk, atomic_read(&csk->refcnt.refcount));
	kref_get(&csk->refcnt);
}