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
struct kpersona_info {scalar_t__* persona_name; scalar_t__* persona_groups; scalar_t__ persona_ngroups; scalar_t__ persona_gid; scalar_t__ persona_type; int /*<<< orphan*/  persona_id; int /*<<< orphan*/  persona_info_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERSONA_INFO_V1 ; 
 int /*<<< orphan*/  PERSONA_OP_FIND ; 
 int __persona (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kpersona_info*,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  strlcpy (scalar_t__*,char const*,int) ; 

int kpersona_find(const char *name, uid_t uid, uid_t *id, size_t *idlen)
{
	int ret;
	struct kpersona_info kinfo;
	kinfo.persona_info_version = PERSONA_INFO_V1;
	kinfo.persona_id = uid;
	kinfo.persona_type = 0;
	kinfo.persona_gid = 0;
	kinfo.persona_ngroups = 0;
	kinfo.persona_groups[0] = 0;
	kinfo.persona_name[0] = 0;
	if (name)
		strlcpy(kinfo.persona_name, name, sizeof(kinfo.persona_name));
	ret = __persona(PERSONA_OP_FIND, 0, &kinfo, id, idlen);
	if (ret < 0)
		return ret;
	return (int)(*idlen);
}