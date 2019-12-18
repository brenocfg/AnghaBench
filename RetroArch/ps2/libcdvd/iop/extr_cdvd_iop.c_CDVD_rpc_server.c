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
 void* CDVDRpc_DiskReady (unsigned int*) ; 
 void* CDVDRpc_FindFile (unsigned int*) ; 
 void* CDVDRpc_FlushCache () ; 
 void* CDVDRpc_Getdir (unsigned int*) ; 
 void* CDVDRpc_Stop () ; 
 void* CDVDRpc_TrayReq (unsigned int*) ; 
#define  CDVD_DISKREADY 133 
#define  CDVD_FINDFILE 132 
#define  CDVD_FLUSHCACHE 131 
#define  CDVD_GETDIR 130 
#define  CDVD_STOP 129 
#define  CDVD_TRAYREQ 128 

void *CDVD_rpc_server(int fno, void *data, int size)
{

    switch (fno) {
        case CDVD_FINDFILE:
            return CDVDRpc_FindFile((unsigned *)data);
        case CDVD_GETDIR:
            return CDVDRpc_Getdir((unsigned *)data);
        case CDVD_STOP:
            return CDVDRpc_Stop();
        case CDVD_TRAYREQ:
            return CDVDRpc_TrayReq((unsigned *)data);
        case CDVD_DISKREADY:
            return CDVDRpc_DiskReady((unsigned *)data);
        case CDVD_FLUSHCACHE:
            return CDVDRpc_FlushCache();
    }

    return NULL;
}