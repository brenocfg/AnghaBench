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
struct kern_ipc_perm {int seq; } ;

/* Variables and functions */
 int SEQ_MULTIPLIER ; 

__attribute__((used)) static inline int ipc_checkid(struct kern_ipc_perm *ipcp, int uid)
{
	if (uid / SEQ_MULTIPLIER != ipcp->seq)
		return 1;
	return 0;
}