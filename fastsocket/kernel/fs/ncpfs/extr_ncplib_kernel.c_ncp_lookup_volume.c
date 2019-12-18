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
struct TYPE_2__ {scalar_t__ mode; } ;
struct nw_info_struct {TYPE_1__ nfs; void* lastAccessDate; void* modifyDate; void* creationDate; void* modifyTime; void* creationTime; int /*<<< orphan*/  attributes; scalar_t__ nameLen; int /*<<< orphan*/  entryName; int /*<<< orphan*/  DosDirNum; int /*<<< orphan*/  dirEntNum; int /*<<< orphan*/  volNumber; } ;
struct ncp_server {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aDIR ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct nw_info_struct*,int /*<<< orphan*/ ,int) ; 
 int ncp_get_volume_root (struct ncp_server*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 

int
ncp_lookup_volume(struct ncp_server *server, const char *volname,
		  struct nw_info_struct *target)
{
	int result;

	memset(target, 0, sizeof(*target));
	result = ncp_get_volume_root(server, volname,
			&target->volNumber, &target->dirEntNum, &target->DosDirNum);
	if (result) {
		return result;
	}
	target->nameLen = strlen(volname);
	memcpy(target->entryName, volname, target->nameLen+1);
	target->attributes = aDIR;
	/* set dates to Jan 1, 1986  00:00 */
	target->creationTime = target->modifyTime = cpu_to_le16(0x0000);
	target->creationDate = target->modifyDate = target->lastAccessDate = cpu_to_le16(0x0C21);
	target->nfs.mode = 0;
	return 0;
}