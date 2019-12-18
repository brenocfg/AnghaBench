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
struct proto {int slab_flags; } ;

/* Variables and functions */
 int RHEL_EXTENDED_PROTO ; 

__attribute__((used)) static int proto_slab_flags(const struct proto *prot)
{
	return prot->slab_flags & ~RHEL_EXTENDED_PROTO;
}