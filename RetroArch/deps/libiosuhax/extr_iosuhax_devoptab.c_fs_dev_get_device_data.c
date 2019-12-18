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
typedef  int /*<<< orphan*/  fs_dev_private_t ;
struct TYPE_3__ {scalar_t__ deviceData; scalar_t__ name; } ;
typedef  TYPE_1__ devoptab_t ;

/* Variables and functions */
 int STD_MAX ; 
 TYPE_1__** devoptab_list ; 
 scalar_t__ strcmp (char*,scalar_t__) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int /*<<< orphan*/  strtok (char*,char*) ; 

__attribute__((used)) static fs_dev_private_t *fs_dev_get_device_data(const char *path)
{
    const devoptab_t *devoptab = NULL;
    char name[128] = {0};
    int i;

    if(!path)
        return NULL;

    /* Get the device name from the path */
    strncpy(name, path, 127);
    strtok(name, ":/");

    // Search the devoptab table for the specified device name
    // NOTE: We do this manually due to a 'bug' in GetDeviceOpTab
    //       which ignores names with suffixes and causes names
    //       like "ntfs" and "ntfs1" to be seen as equals
    for (i = 3; i < STD_MAX; i++) {
        devoptab = devoptab_list[i];
        if (devoptab && devoptab->name) {
            if (strcmp(name, devoptab->name) == 0) {
                return (fs_dev_private_t *)devoptab->deviceData;
            }
        }
    }

    return NULL;
}