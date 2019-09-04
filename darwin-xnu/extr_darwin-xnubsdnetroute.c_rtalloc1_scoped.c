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
typedef  int /*<<< orphan*/  uint32_t ;
struct sockaddr {int dummy; } ;
struct rtentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rnh_lock ; 
 struct rtentry* rtalloc1_scoped_locked (struct sockaddr*,int,int /*<<< orphan*/ ,unsigned int) ; 

struct rtentry *
rtalloc1_scoped(struct sockaddr *dst, int report, uint32_t ignflags,
    unsigned int ifscope)
{
	struct rtentry *entry;
	LCK_MTX_ASSERT(rnh_lock, LCK_MTX_ASSERT_NOTOWNED);
	lck_mtx_lock(rnh_lock);
	entry = rtalloc1_scoped_locked(dst, report, ignflags, ifscope);
	lck_mtx_unlock(rnh_lock);
	return (entry);
}