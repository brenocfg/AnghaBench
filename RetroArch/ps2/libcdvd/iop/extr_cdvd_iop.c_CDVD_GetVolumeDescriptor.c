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
struct cdVolDesc {int filesystemType; int /*<<< orphan*/  volID; } ;
struct TYPE_3__ {int filesystemType; } ;

/* Variables and functions */
 TYPE_1__ CDVolDesc ; 
 int /*<<< orphan*/  ReadSect (int,int,struct cdVolDesc*,int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int /*<<< orphan*/  cdReadMode ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct cdVolDesc*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

int CDVD_GetVolumeDescriptor(void)
{
    // Read until we find the last valid Volume Descriptor
    int volDescSector;

    static struct cdVolDesc localVolDesc;

#ifdef DEBUG
    printf("CDVD_GetVolumeDescriptor called\n");
#endif

    for (volDescSector = 16; volDescSector < 20; volDescSector++) {
        ReadSect(volDescSector, 1, &localVolDesc, &cdReadMode);

        // If this is still a volume Descriptor
        if (strncmp(localVolDesc.volID, "CD001", 5) == 0) {
            if ((localVolDesc.filesystemType == 1) ||
                (localVolDesc.filesystemType == 2)) {
                memcpy(&CDVolDesc, &localVolDesc, sizeof(struct cdVolDesc));
            }
        } else
            break;
    }

#ifdef DEBUG
    switch (CDVolDesc.filesystemType) {
        case 1:
            printf("CD FileSystem is ISO9660\n");
            break;

        case 2:
            printf("CD FileSystem is Joliet\n");
            break;

        default:
            printf("CD FileSystem is unknown type\n");
            break;
    }
#endif
    //	sceCdStop();

    return TRUE;
}