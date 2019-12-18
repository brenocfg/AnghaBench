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
struct proto {int slab_flags; int rhel_flags; } ;

/* Variables and functions */
 int RHEL_EXTENDED_PROTO ; 

__attribute__((used)) static bool proto_has_rhel_ext(const struct proto *prot, int flag)
{
	return (prot->slab_flags & RHEL_EXTENDED_PROTO) &&
	       (prot->rhel_flags & flag);
}