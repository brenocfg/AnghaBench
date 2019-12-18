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
typedef  int /*<<< orphan*/  uid_t ;
struct kpersona_info {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PERSONA_OP_PIDINFO ; 
 int __persona (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kpersona_info*,int /*<<< orphan*/ *,size_t*) ; 

int kpersona_pidinfo(pid_t pid, struct kpersona_info *info)
{
	size_t idlen = 1;
	uid_t id = (uid_t)pid;
	return __persona(PERSONA_OP_PIDINFO, 0, info, &id, &idlen);
}