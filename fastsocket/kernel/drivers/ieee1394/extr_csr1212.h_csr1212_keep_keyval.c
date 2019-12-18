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
struct csr1212_keyval {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic_inc () ; 

__attribute__((used)) static inline void csr1212_keep_keyval(struct csr1212_keyval *kv)
{
	atomic_inc(&kv->refcnt);
	smp_mb__after_atomic_inc();
}