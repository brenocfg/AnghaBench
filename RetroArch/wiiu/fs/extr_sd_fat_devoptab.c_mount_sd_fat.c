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
typedef  int /*<<< orphan*/  FSCmdBlock ;
typedef  int /*<<< orphan*/  FSClient ;

/* Variables and functions */
 int /*<<< orphan*/  FSAddClient (void*,int) ; 
 int /*<<< orphan*/  FSInit () ; 
 int /*<<< orphan*/  FSInitCmdBlock (void*) ; 
 scalar_t__ MountFS (void*,void*,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 void* malloc (int) ; 
 int sd_fat_add_device (char const*,char*,void*,void*) ; 

int mount_sd_fat(const char *path)
{
    int result = -1;

    /* get command and client */
    void* pClient = malloc(sizeof(FSClient));
    void* pCmd = malloc(sizeof(FSCmdBlock));

    if(!pClient || !pCmd) {
        /* just in case free if not 0 */
        if(pClient)
            free(pClient);
        if(pCmd)
            free(pCmd);
        return -2;
    }

    FSInit();
    FSInitCmdBlock(pCmd);
    FSAddClient(pClient, -1);

    char *mountPath = NULL;

    if(MountFS(pClient, pCmd, &mountPath) == 0) {
        result = sd_fat_add_device(path, mountPath, pClient, pCmd);
        free(mountPath);
    }

    return result;
}