#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct proc_dir_entry {void* gid; void* uid; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct airo_info {char* proc_name; TYPE_1__* proc_entry; } ;
struct TYPE_6__ {void* gid; void* uid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int S_IFDIR ; 
 int S_IFREG ; 
 int S_IRUGO ; 
 TYPE_1__* airo_entry ; 
 int airo_perm ; 
 TYPE_1__* create_proc_entry (char*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  proc_APList_ops ; 
 int /*<<< orphan*/  proc_BSSList_ops ; 
 int /*<<< orphan*/  proc_SSID_ops ; 
 int /*<<< orphan*/  proc_config_ops ; 
 struct proc_dir_entry* proc_create_data (char*,int,TYPE_1__*,int /*<<< orphan*/ *,struct net_device*) ; 
 void* proc_gid ; 
 int proc_perm ; 
 int /*<<< orphan*/  proc_stats_ops ; 
 int /*<<< orphan*/  proc_statsdelta_ops ; 
 int /*<<< orphan*/  proc_status_ops ; 
 void* proc_uid ; 
 int /*<<< orphan*/  proc_wepkey_ops ; 
 int /*<<< orphan*/  remove_proc_entry (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_proc_entry( struct net_device *dev,
			     struct airo_info *apriv ) {
	struct proc_dir_entry *entry;
	/* First setup the device directory */
	strcpy(apriv->proc_name,dev->name);
	apriv->proc_entry = create_proc_entry(apriv->proc_name,
					      S_IFDIR|airo_perm,
					      airo_entry);
	if (!apriv->proc_entry)
		goto fail;
	apriv->proc_entry->uid = proc_uid;
	apriv->proc_entry->gid = proc_gid;

	/* Setup the StatsDelta */
	entry = proc_create_data("StatsDelta",
				 S_IFREG | (S_IRUGO&proc_perm),
				 apriv->proc_entry, &proc_statsdelta_ops, dev);
	if (!entry)
		goto fail_stats_delta;
	entry->uid = proc_uid;
	entry->gid = proc_gid;

	/* Setup the Stats */
	entry = proc_create_data("Stats",
				 S_IFREG | (S_IRUGO&proc_perm),
				 apriv->proc_entry, &proc_stats_ops, dev);
	if (!entry)
		goto fail_stats;
	entry->uid = proc_uid;
	entry->gid = proc_gid;

	/* Setup the Status */
	entry = proc_create_data("Status",
				 S_IFREG | (S_IRUGO&proc_perm),
				 apriv->proc_entry, &proc_status_ops, dev);
	if (!entry)
		goto fail_status;
	entry->uid = proc_uid;
	entry->gid = proc_gid;

	/* Setup the Config */
	entry = proc_create_data("Config",
				 S_IFREG | proc_perm,
				 apriv->proc_entry, &proc_config_ops, dev);
	if (!entry)
		goto fail_config;
	entry->uid = proc_uid;
	entry->gid = proc_gid;

	/* Setup the SSID */
	entry = proc_create_data("SSID",
				 S_IFREG | proc_perm,
				 apriv->proc_entry, &proc_SSID_ops, dev);
	if (!entry)
		goto fail_ssid;
	entry->uid = proc_uid;
	entry->gid = proc_gid;

	/* Setup the APList */
	entry = proc_create_data("APList",
				 S_IFREG | proc_perm,
				 apriv->proc_entry, &proc_APList_ops, dev);
	if (!entry)
		goto fail_aplist;
	entry->uid = proc_uid;
	entry->gid = proc_gid;

	/* Setup the BSSList */
	entry = proc_create_data("BSSList",
				 S_IFREG | proc_perm,
				 apriv->proc_entry, &proc_BSSList_ops, dev);
	if (!entry)
		goto fail_bsslist;
	entry->uid = proc_uid;
	entry->gid = proc_gid;

	/* Setup the WepKey */
	entry = proc_create_data("WepKey",
				 S_IFREG | proc_perm,
				 apriv->proc_entry, &proc_wepkey_ops, dev);
	if (!entry)
		goto fail_wepkey;
	entry->uid = proc_uid;
	entry->gid = proc_gid;

	return 0;

fail_wepkey:
	remove_proc_entry("BSSList", apriv->proc_entry);
fail_bsslist:
	remove_proc_entry("APList", apriv->proc_entry);
fail_aplist:
	remove_proc_entry("SSID", apriv->proc_entry);
fail_ssid:
	remove_proc_entry("Config", apriv->proc_entry);
fail_config:
	remove_proc_entry("Status", apriv->proc_entry);
fail_status:
	remove_proc_entry("Stats", apriv->proc_entry);
fail_stats:
	remove_proc_entry("StatsDelta", apriv->proc_entry);
fail_stats_delta:
	remove_proc_entry(apriv->proc_name, airo_entry);
fail:
	return -ENOMEM;
}