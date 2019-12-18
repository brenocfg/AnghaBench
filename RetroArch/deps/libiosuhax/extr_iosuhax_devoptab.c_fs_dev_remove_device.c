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
struct TYPE_5__ {TYPE_2__* pMutex; int /*<<< orphan*/  mount_path; int /*<<< orphan*/  fsaFd; scalar_t__ mounted; } ;
typedef  TYPE_1__ fs_dev_private_t ;
struct TYPE_6__ {struct TYPE_6__* deviceData; scalar_t__ name; } ;
typedef  TYPE_2__ devoptab_t ;

/* Variables and functions */
 int /*<<< orphan*/  IOSUHAX_FSA_Unmount (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int STD_MAX ; 
 TYPE_2__** devoptab_list ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ strcmp (char*,scalar_t__) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int /*<<< orphan*/  strtok (char*,char*) ; 

__attribute__((used)) static int fs_dev_remove_device (const char *path)
{
    const devoptab_t *devoptab = NULL;
    char name[128] = {0};
    int i;

    if(!path)
        return -1;

    // Get the device name from the path
    strncpy(name, path, 127);
    strtok(name, ":/");

    // Find and remove the specified device from the devoptab table
    // NOTE: We do this manually due to a 'bug' in RemoveDevice
    //       which ignores names with suffixes and causes names
    //       like "ntfs" and "ntfs1" to be seen as equals
    for (i = 3; i < STD_MAX; i++) {
        devoptab = devoptab_list[i];
        if (devoptab && devoptab->name) {
            if (strcmp(name, devoptab->name) == 0) {
                devoptab_list[i] = devoptab_list[0];

                if(devoptab->deviceData)
                {
                    fs_dev_private_t *priv = (fs_dev_private_t *)devoptab->deviceData;

                    if(priv->mounted)
                        IOSUHAX_FSA_Unmount(priv->fsaFd, priv->mount_path, 2);

                    if(priv->pMutex)
                        free(priv->pMutex);
                    free(devoptab->deviceData);
                }

                free((devoptab_t*)devoptab);
                return 0;
            }
        }
    }

    return -1;
}