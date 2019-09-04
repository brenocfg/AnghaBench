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

/* Variables and functions */
 int /*<<< orphan*/  DEVFS_LOCK () ; 
 int /*<<< orphan*/  DEVFS_UNLOCK () ; 
 int /*<<< orphan*/  DEV_DIR ; 
 int ENOTSUP ; 
 int dev_add_entry (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_root ; 
 int /*<<< orphan*/  devfs_attr_mutex ; 
 int /*<<< orphan*/  devfs_lck_attr ; 
 int /*<<< orphan*/  devfs_lck_grp ; 
 int /*<<< orphan*/  devfs_lck_grp_attr ; 
 int /*<<< orphan*/  devfs_mutex ; 
 int devfs_ready ; 
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
devfs_sinit(void)
{
    int error;

    devfs_lck_grp_attr = lck_grp_attr_alloc_init();
	devfs_lck_grp = lck_grp_alloc_init("devfs_lock", devfs_lck_grp_attr);

	devfs_lck_attr = lck_attr_alloc_init();

	lck_mtx_init(&devfs_mutex, devfs_lck_grp, devfs_lck_attr);
	lck_mtx_init(&devfs_attr_mutex, devfs_lck_grp, devfs_lck_attr);

	DEVFS_LOCK();
        error = dev_add_entry("root", NULL, DEV_DIR, NULL, NULL, NULL, &dev_root);
	DEVFS_UNLOCK();

	if (error) {
	    printf("devfs_sinit: dev_add_entry failed ");
	    return (ENOTSUP);
	}
#ifdef HIDDEN_MOUNTPOINT
	MALLOC(devfs_hidden_mount, struct mount *, sizeof(struct mount),
	       M_MOUNT, M_WAITOK);
	bzero(devfs_hidden_mount,sizeof(struct mount));
	mount_lock_init(devfs_hidden_mount);
	TAILQ_INIT(&devfs_hidden_mount->mnt_vnodelist);
	TAILQ_INIT(&devfs_hidden_mount->mnt_workerqueue);
	TAILQ_INIT(&devfs_hidden_mount->mnt_newvnodes);
#if CONFIG_MACF
	mac_mount_label_init(devfs_hidden_mount);
	mac_mount_label_associate(vfs_context_kernel(), devfs_hidden_mount);
#endif

	/* Initialize the default IO constraints */
	mp->mnt_maxreadcnt = mp->mnt_maxwritecnt = MAXPHYS;
	mp->mnt_segreadcnt = mp->mnt_segwritecnt = 32;
	mp->mnt_ioflags = 0;
	mp->mnt_realrootvp = NULLVP;
	mp->mnt_authcache_ttl = CACHED_LOOKUP_RIGHT_TTL;

	devfs_mount(devfs_hidden_mount,"dummy",NULL,NULL,NULL);
	dev_root->de_dnp->dn_dvm 
	    = (struct devfsmount *)devfs_hidden_mount->mnt_data;
#endif /* HIDDEN_MOUNTPOINT */
#if CONFIG_MACF
	mac_devfs_label_associate_directory("/", strlen("/"),
	    dev_root->de_dnp, "/");
#endif
	devfs_ready = 1;
	return (0);
}