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
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct afs_call {scalar_t__ reply_size; scalar_t__ reply_max; int /*<<< orphan*/ * buffer; struct afs_cache_vlocation* reply; } ;
struct afs_cache_vlocation {int /*<<< orphan*/  vidmask; void** vid; int /*<<< orphan*/ * srvtmask; TYPE_1__* servers; void* nservers; void** name; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;

/* Variables and functions */
 int AFS_VLF_BACKEXISTS ; 
 int AFS_VLF_ROEXISTS ; 
 int AFS_VLF_RWEXISTS ; 
 int AFS_VLSF_BACKVOL ; 
 int AFS_VLSF_ROVOL ; 
 int AFS_VLSF_RWVOL ; 
 int /*<<< orphan*/  AFS_VOL_VTM_BAK ; 
 int /*<<< orphan*/  AFS_VOL_VTM_RO ; 
 int /*<<< orphan*/  AFS_VOL_VTM_RW ; 
 int EBADMSG ; 
 int /*<<< orphan*/  _enter (char*,int) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  afs_transfer_reply (struct afs_call*,struct sk_buff*) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int afs_deliver_vl_get_entry_by_xxx(struct afs_call *call,
					   struct sk_buff *skb, bool last)
{
	struct afs_cache_vlocation *entry;
	__be32 *bp;
	u32 tmp;
	int loop;

	_enter(",,%u", last);

	afs_transfer_reply(call, skb);
	if (!last)
		return 0;

	if (call->reply_size != call->reply_max)
		return -EBADMSG;

	/* unmarshall the reply once we've received all of it */
	entry = call->reply;
	bp = call->buffer;

	for (loop = 0; loop < 64; loop++)
		entry->name[loop] = ntohl(*bp++);
	entry->name[loop] = 0;
	bp++; /* final NUL */

	bp++; /* type */
	entry->nservers = ntohl(*bp++);

	for (loop = 0; loop < 8; loop++)
		entry->servers[loop].s_addr = *bp++;

	bp += 8; /* partition IDs */

	for (loop = 0; loop < 8; loop++) {
		tmp = ntohl(*bp++);
		entry->srvtmask[loop] = 0;
		if (tmp & AFS_VLSF_RWVOL)
			entry->srvtmask[loop] |= AFS_VOL_VTM_RW;
		if (tmp & AFS_VLSF_ROVOL)
			entry->srvtmask[loop] |= AFS_VOL_VTM_RO;
		if (tmp & AFS_VLSF_BACKVOL)
			entry->srvtmask[loop] |= AFS_VOL_VTM_BAK;
	}

	entry->vid[0] = ntohl(*bp++);
	entry->vid[1] = ntohl(*bp++);
	entry->vid[2] = ntohl(*bp++);

	bp++; /* clone ID */

	tmp = ntohl(*bp++); /* flags */
	entry->vidmask = 0;
	if (tmp & AFS_VLF_RWEXISTS)
		entry->vidmask |= AFS_VOL_VTM_RW;
	if (tmp & AFS_VLF_ROEXISTS)
		entry->vidmask |= AFS_VOL_VTM_RO;
	if (tmp & AFS_VLF_BACKEXISTS)
		entry->vidmask |= AFS_VOL_VTM_BAK;
	if (!entry->vidmask)
		return -EBADMSG;

	_leave(" = 0 [done]");
	return 0;
}