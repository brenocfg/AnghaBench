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
struct kern_ipc_perm {char* security; } ;

/* Variables and functions */
 int /*<<< orphan*/  smack_to_secid (char*) ; 

__attribute__((used)) static void smack_ipc_getsecid(struct kern_ipc_perm *ipp, u32 *secid)
{
	char *smack = ipp->security;

	*secid = smack_to_secid(smack);
}