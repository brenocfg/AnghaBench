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
 int /*<<< orphan*/  FSDelClient (void*,int) ; 
 int /*<<< orphan*/  UmountFS (void*,void*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int sd_fat_remove_device (char const*,void**,void**,char**) ; 

int unmount_sd_fat(const char *path)
{
    void *pClient = 0;
    void *pCmd = 0;
    char *mountPath = 0;

    int result = sd_fat_remove_device(path, &pClient, &pCmd, &mountPath);
    if(result == 0)
    {
        UmountFS(pClient, pCmd, mountPath);
        FSDelClient(pClient, -1);
        free(pClient);
        free(pCmd);
        free(mountPath);
        /* FSShutdown(); */
    }
    return result;
}