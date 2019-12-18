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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_name_seq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsv_publ_ok ; 
 int tipc_publish (int /*<<< orphan*/ ,unsigned int,struct tipc_name_seq const*) ; 

int tipc_nametbl_publish_rsv(u32 ref, unsigned int scope,
			struct tipc_name_seq const *seq)
{
	int res;

	atomic_inc(&rsv_publ_ok);
	res = tipc_publish(ref, scope, seq);
	atomic_dec(&rsv_publ_ok);
	return res;
}