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
struct if_proto {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add_32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
if_proto_ref(struct if_proto *proto)
{
	atomic_add_32(&proto->refcount, 1);
}