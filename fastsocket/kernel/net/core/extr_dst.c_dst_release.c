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
struct dst_entry {int /*<<< orphan*/  __refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__before_atomic_dec () ; 

void dst_release(struct dst_entry *dst)
{
	if (dst) {
               int newrefcnt;

		smp_mb__before_atomic_dec();
               newrefcnt = atomic_dec_return(&dst->__refcnt);
	       //FPRINTK("Release dst 0x%p[%u]\n", dst, atomic_read(&dst->__refcnt));
               WARN_ON(newrefcnt < 0);
	}
}