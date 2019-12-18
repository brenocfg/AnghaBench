#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct proc_dir_entry {struct net_device* data; } ;
struct proc_data {char* wbuffer; int writelen; } ;
struct net_device {struct airo_info* ml_priv; } ;
struct inode {int dummy; } ;
struct file {scalar_t__ private_data; } ;
struct airo_info {int dummy; } ;
struct TYPE_6__ {void* len; TYPE_1__* ssids; } ;
struct TYPE_5__ {void* len; int /*<<< orphan*/ * ssid; } ;
typedef  TYPE_2__ SsidRid ;
typedef  int /*<<< orphan*/  SSID_rid ;

/* Variables and functions */
 struct proc_dir_entry* PDE (struct inode*) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  disable_MAC (struct airo_info*,int) ; 
 int /*<<< orphan*/  enable_MAC (struct airo_info*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writeSsidRid (struct airo_info*,TYPE_2__*,int) ; 

__attribute__((used)) static void proc_SSID_on_close(struct inode *inode, struct file *file)
{
	struct proc_data *data = (struct proc_data *)file->private_data;
	struct proc_dir_entry *dp = PDE(inode);
	struct net_device *dev = dp->data;
	struct airo_info *ai = dev->ml_priv;
	SsidRid SSID_rid;
	int i;
	char *p = data->wbuffer;
	char *end = p + data->writelen;

	if (!data->writelen)
		return;

	*end = '\n'; /* sentinel; we have space for it */

	memset(&SSID_rid, 0, sizeof(SSID_rid));

	for (i = 0; i < 3 && p < end; i++) {
		int j = 0;
		/* copy up to 32 characters from this line */
		while (*p != '\n' && j < 32)
			SSID_rid.ssids[i].ssid[j++] = *p++;
		if (j == 0)
			break;
		SSID_rid.ssids[i].len = cpu_to_le16(j);
		/* skip to the beginning of the next line */
		while (*p++ != '\n')
			;
	}
	if (i)
		SSID_rid.len = cpu_to_le16(sizeof(SSID_rid));
	disable_MAC(ai, 1);
	writeSsidRid(ai, &SSID_rid, 1);
	enable_MAC(ai, 1);
}