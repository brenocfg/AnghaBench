#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wkr ;
struct proc_dir_entry {struct net_device* data; } ;
struct proc_data {char* rbuffer; int maxwritelen; int /*<<< orphan*/  readlen; int /*<<< orphan*/  on_close; int /*<<< orphan*/ * wbuffer; scalar_t__ writelen; } ;
struct net_device {struct airo_info* ml_priv; } ;
struct inode {int dummy; } ;
struct file {char* private_data; } ;
struct airo_info {int dummy; } ;
typedef  scalar_t__ __le16 ;
struct TYPE_4__ {scalar_t__ kindex; scalar_t__ klen; scalar_t__* mac; } ;
typedef  TYPE_1__ WepKeyRid ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct proc_dir_entry* PDE (struct inode*) ; 
 int SUCCESS ; 
 scalar_t__ cpu_to_le16 (int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  proc_wepkey_on_close ; 
 int readWepKeyRid (struct airo_info*,TYPE_1__*,int,int) ; 
 scalar_t__ sprintf (char*,char*,int,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int proc_wepkey_open( struct inode *inode, struct file *file )
{
	struct proc_data *data;
	struct proc_dir_entry *dp = PDE(inode);
	struct net_device *dev = dp->data;
	struct airo_info *ai = dev->ml_priv;
	char *ptr;
	WepKeyRid wkr;
	__le16 lastindex;
	int j=0;
	int rc;

	if ((file->private_data = kzalloc(sizeof(struct proc_data ), GFP_KERNEL)) == NULL)
		return -ENOMEM;
	memset(&wkr, 0, sizeof(wkr));
	data = (struct proc_data *)file->private_data;
	if ((data->rbuffer = kzalloc( 180, GFP_KERNEL )) == NULL) {
		kfree (file->private_data);
		return -ENOMEM;
	}
	data->writelen = 0;
	data->maxwritelen = 80;
	if ((data->wbuffer = kzalloc( 80, GFP_KERNEL )) == NULL) {
		kfree (data->rbuffer);
		kfree (file->private_data);
		return -ENOMEM;
	}
	data->on_close = proc_wepkey_on_close;

	ptr = data->rbuffer;
	strcpy(ptr, "No wep keys\n");
	rc = readWepKeyRid(ai, &wkr, 1, 1);
	if (rc == SUCCESS) do {
		lastindex = wkr.kindex;
		if (wkr.kindex == cpu_to_le16(0xffff)) {
			j += sprintf(ptr+j, "Tx key = %d\n",
				     (int)wkr.mac[0]);
		} else {
			j += sprintf(ptr+j, "Key %d set with length = %d\n",
				     le16_to_cpu(wkr.kindex),
				     le16_to_cpu(wkr.klen));
		}
		readWepKeyRid(ai, &wkr, 0, 1);
	} while((lastindex != wkr.kindex) && (j < 180-30));

	data->readlen = strlen( data->rbuffer );
	return 0;
}