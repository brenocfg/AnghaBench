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
struct ipx_interface {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ipxitf_down (struct ipx_interface*) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline__ void __ipxitf_put(struct ipx_interface *intrfc)
{
	if (atomic_dec_and_test(&intrfc->refcnt))
		__ipxitf_down(intrfc);
}