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
struct TYPE_2__ {int /*<<< orphan*/  gettod_r; int /*<<< orphan*/  exit; int /*<<< orphan*/  malloc_unlock; int /*<<< orphan*/  malloc_lock; int /*<<< orphan*/  lock_acquire; int /*<<< orphan*/  lock_release; int /*<<< orphan*/  lock_close; int /*<<< orphan*/  lock_init; int /*<<< orphan*/  sbrk_r; } ;

/* Variables and functions */
 int /*<<< orphan*/  __libogc_exit ; 
 int /*<<< orphan*/  __libogc_gettod_r ; 
 int /*<<< orphan*/  __libogc_lock_acquire ; 
 int /*<<< orphan*/  __libogc_lock_close ; 
 int /*<<< orphan*/  __libogc_lock_init ; 
 int /*<<< orphan*/  __libogc_lock_release ; 
 int /*<<< orphan*/  __libogc_malloc_lock ; 
 int /*<<< orphan*/  __libogc_malloc_unlock ; 
 int /*<<< orphan*/  __libogc_sbrk_r ; 
 TYPE_1__ __syscalls ; 

__attribute__((used)) static void __init_syscall_array() {
	__syscalls.sbrk_r = __libogc_sbrk_r;
	__syscalls.lock_init = __libogc_lock_init;
	__syscalls.lock_close = __libogc_lock_close;
	__syscalls.lock_release = __libogc_lock_release;
	__syscalls.lock_acquire = __libogc_lock_acquire;
	__syscalls.malloc_lock = __libogc_malloc_lock;
	__syscalls.malloc_unlock = __libogc_malloc_unlock;
	__syscalls.exit = __libogc_exit;
	__syscalls.gettod_r = __libogc_gettod_r;

}