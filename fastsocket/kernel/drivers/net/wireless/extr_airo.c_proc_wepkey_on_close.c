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
typedef  char u16 ;
struct proc_dir_entry {struct net_device* data; } ;
struct proc_data {char* wbuffer; int /*<<< orphan*/  writelen; } ;
struct net_device {struct airo_info* ml_priv; } ;
struct inode {int dummy; } ;
struct file {scalar_t__ private_data; } ;
struct airo_info {TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  key ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct proc_dir_entry* PDE (struct inode*) ; 
 int /*<<< orphan*/  airo_print_err (int /*<<< orphan*/ ,char*,...) ; 
 char hexVal (char) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int set_wep_key (struct airo_info*,char,char*,int,int,int) ; 
 int set_wep_tx_idx (struct airo_info*,char,int,int) ; 

__attribute__((used)) static void proc_wepkey_on_close( struct inode *inode, struct file *file ) {
	struct proc_data *data;
	struct proc_dir_entry *dp = PDE(inode);
	struct net_device *dev = dp->data;
	struct airo_info *ai = dev->ml_priv;
	int i, rc;
	char key[16];
	u16 index = 0;
	int j = 0;

	memset(key, 0, sizeof(key));

	data = (struct proc_data *)file->private_data;
	if ( !data->writelen ) return;

	if (data->wbuffer[0] >= '0' && data->wbuffer[0] <= '3' &&
	    (data->wbuffer[1] == ' ' || data->wbuffer[1] == '\n')) {
		index = data->wbuffer[0] - '0';
		if (data->wbuffer[1] == '\n') {
			rc = set_wep_tx_idx(ai, index, 1, 1);
			if (rc < 0) {
				airo_print_err(ai->dev->name, "failed to set "
				               "WEP transmit index to %d: %d.",
				               index, rc);
			}
			return;
		}
		j = 2;
	} else {
		airo_print_err(ai->dev->name, "WepKey passed invalid key index");
		return;
	}

	for( i = 0; i < 16*3 && data->wbuffer[i+j]; i++ ) {
		switch(i%3) {
		case 0:
			key[i/3] = hexVal(data->wbuffer[i+j])<<4;
			break;
		case 1:
			key[i/3] |= hexVal(data->wbuffer[i+j]);
			break;
		}
	}

	rc = set_wep_key(ai, index, key, i/3, 1, 1);
	if (rc < 0) {
		airo_print_err(ai->dev->name, "failed to set WEP key at index "
		               "%d: %d.", index, rc);
	}
}