#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* g_guid; } ;
typedef  TYPE_1__ guid_t ;

/* Variables and functions */
 int NFS_IDMAP_CTRL_LOG_FAILED_MAPPINGS ; 
 int NFS_IDMAP_CTRL_LOG_SUCCESSFUL_MAPPINGS ; 
 int nfs_idmap_ctrl ; 
 int /*<<< orphan*/  printf (char*,char const*,char*,int,...) ; 

__attribute__((used)) static void
nfs4_mapid_log(int error, const char *idstr, int isgroup, guid_t *gp)
{
	if (error && (nfs_idmap_ctrl & NFS_IDMAP_CTRL_LOG_FAILED_MAPPINGS))
		printf("nfs4_id2guid: idmap failed for %s %s error %d\n",  idstr, isgroup ? "G" : " ", error);
	if (!error && (nfs_idmap_ctrl & NFS_IDMAP_CTRL_LOG_SUCCESSFUL_MAPPINGS))
		printf("nfs4_id2guid: idmap for %s %s got guid "
		       "%02x%02x%02x%02x_%02x%02x%02x%02x_%02x%02x%02x%02x_%02x%02x%02x%02x\n",
		       idstr, isgroup ? "G" : " ",
		       gp->g_guid[0], gp->g_guid[1], gp->g_guid[2], gp->g_guid[3],
		       gp->g_guid[4], gp->g_guid[5], gp->g_guid[6], gp->g_guid[7],
		       gp->g_guid[8], gp->g_guid[9], gp->g_guid[10], gp->g_guid[11],
		       gp->g_guid[12], gp->g_guid[13], gp->g_guid[14], gp->g_guid[15]);
}