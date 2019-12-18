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
struct TYPE_6__ {char* mount_path; int fsaFd; int mounted; char* name; struct TYPE_6__* deviceData; scalar_t__ pMutex; } ;
typedef  TYPE_1__ fs_dev_private_t ;
typedef  TYPE_1__ devoptab_t ;

/* Variables and functions */
 int /*<<< orphan*/  EADDRNOTAVAIL ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  OSInitMutex (scalar_t__) ; 
 scalar_t__ OS_MUTEX_SIZE ; 
 int STD_MAX ; 
 int /*<<< orphan*/  devops_fs ; 
 TYPE_1__** devoptab_list ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int fs_dev_add_device (const char *name, const char *mount_path, int fsaFd, int isMounted)
{
    devoptab_t *dev = NULL;
    char *devname = NULL;
    char *devpath = NULL;
    int i;

    // Sanity check
    if (!name || !mount_path) {
        errno = EINVAL;
        return -1;
    }

    // Allocate a devoptab for this device
    dev = (devoptab_t *) malloc(sizeof(devoptab_t) + strlen(name) + 1);
    if (!dev) {
        errno = ENOMEM;
        return -1;
    }

    // Use the space allocated at the end of the devoptab for storing the device name
    devname = (char*)(dev + 1);
    strcpy(devname, name);

    // create private data
    fs_dev_private_t *priv = (fs_dev_private_t *)malloc(sizeof(fs_dev_private_t) + strlen(mount_path) + 1);
    if(!priv) {
        free(dev);
        errno = ENOMEM;
        return -1;
    }

    devpath = (char*)(priv+1);
    strcpy(devpath, mount_path);

    // setup private data
    priv->mount_path = devpath;
    priv->fsaFd = fsaFd;
    priv->mounted = isMounted;
    priv->pMutex = malloc(OS_MUTEX_SIZE);

    if(!priv->pMutex) {
        free(dev);
        free(priv);
        errno = ENOMEM;
        return -1;
    }

    OSInitMutex(priv->pMutex);

    // Setup the devoptab
    memcpy(dev, &devops_fs, sizeof(devoptab_t));
    dev->name = devname;
    dev->deviceData = priv;

    // Add the device to the devoptab table (if there is a free slot)
    for (i = 3; i < STD_MAX; i++) {
        if (devoptab_list[i] == devoptab_list[0]) {
            devoptab_list[i] = dev;
            return 0;
        }
    }

    // failure, free all memory
    free(priv);
    free(dev);

    // If we reach here then there are no free slots in the devoptab table for this device
    errno = EADDRNOTAVAIL;
    return -1;
}