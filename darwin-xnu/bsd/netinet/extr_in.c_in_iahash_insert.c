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
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_4__ {scalar_t__ sin_family; TYPE_1__ sin_addr; } ;
struct in_ifaddr {int /*<<< orphan*/  ia_ifa; TYPE_2__ ia_addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ IA_IS_HASHED (struct in_ifaddr*) ; 
 int /*<<< orphan*/  IFA_ADDREF_LOCKED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFA_LOCK_ASSERT_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INADDR_HASH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_RW_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_RW_ASSERT_EXCLUSIVE ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ ,struct in_ifaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ia_hash ; 
 int /*<<< orphan*/  in_ifaddr_rwlock ; 
 int /*<<< orphan*/  panic (char*,struct in_ifaddr*) ; 

__attribute__((used)) static void
in_iahash_insert(struct in_ifaddr *ia)
{
	LCK_RW_ASSERT(in_ifaddr_rwlock, LCK_RW_ASSERT_EXCLUSIVE);
	IFA_LOCK_ASSERT_HELD(&ia->ia_ifa);

	if (ia->ia_addr.sin_family != AF_INET) {
		panic("attempt to insert wrong ia %p into hash table\n", ia);
		/* NOTREACHED */
	} else if (IA_IS_HASHED(ia)) {
		panic("attempt to double-insert ia %p into hash table\n", ia);
		/* NOTREACHED */
	}
	TAILQ_INSERT_HEAD(INADDR_HASH(ia->ia_addr.sin_addr.s_addr),
	    ia, ia_hash);
	IFA_ADDREF_LOCKED(&ia->ia_ifa);
}