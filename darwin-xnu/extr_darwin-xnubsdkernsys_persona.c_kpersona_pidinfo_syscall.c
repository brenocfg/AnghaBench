#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user_addr_t ;
struct persona {int /*<<< orphan*/  pna_login; int /*<<< orphan*/  pna_type; int /*<<< orphan*/  pna_id; } ;
struct kpersona_info {unsigned int persona_ngroups; int /*<<< orphan*/  persona_name; int /*<<< orphan*/  persona_gmuid; int /*<<< orphan*/  persona_groups; int /*<<< orphan*/  persona_gid; int /*<<< orphan*/  persona_type; int /*<<< orphan*/  persona_id; int /*<<< orphan*/  persona_info_version; } ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  pid ;
typedef  int /*<<< orphan*/  kinfo ;
struct TYPE_2__ {scalar_t__ p_pid; } ;

/* Variables and functions */
 int EPERM ; 
 int ESRCH ; 
 int /*<<< orphan*/  MAXLOGNAME ; 
 int /*<<< orphan*/  NGROUPS ; 
 int /*<<< orphan*/  PERSONA_INFO_V1 ; 
 int copyin (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 TYPE_1__* current_proc () ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int /*<<< orphan*/  kauth_cred_issuser (int /*<<< orphan*/ ) ; 
 int kpersona_copyout (struct kpersona_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct kpersona_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  persona_get_gid (struct persona*) ; 
 int /*<<< orphan*/  persona_get_gmuid (struct persona*) ; 
 int /*<<< orphan*/  persona_get_groups (struct persona*,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct persona* persona_proc_get (scalar_t__) ; 
 int /*<<< orphan*/  persona_put (struct persona*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kpersona_pidinfo_syscall(user_addr_t idp, user_addr_t infop)
{
	int error;
	pid_t pid;
	struct persona *persona;
	struct kpersona_info kinfo;

	error = copyin(idp, &pid, sizeof(pid));
	if (error)
		return error;

	if (!kauth_cred_issuser(kauth_cred_get())
	    && (pid != current_proc()->p_pid))
		return EPERM;

	persona = persona_proc_get(pid);
	if (!persona)
		return ESRCH;

	memset(&kinfo, 0, sizeof(kinfo));
	kinfo.persona_info_version = PERSONA_INFO_V1;
	kinfo.persona_id = persona->pna_id;
	kinfo.persona_type = persona->pna_type;
	kinfo.persona_gid = persona_get_gid(persona);
	unsigned ngroups = 0;
	persona_get_groups(persona, &ngroups, kinfo.persona_groups, NGROUPS);
	kinfo.persona_ngroups = ngroups;
	kinfo.persona_gmuid = persona_get_gmuid(persona);

	strncpy(kinfo.persona_name, persona->pna_login, MAXLOGNAME);

	persona_put(persona);

	error = kpersona_copyout(&kinfo, infop);

	return error;
}