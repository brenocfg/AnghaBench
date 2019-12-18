#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dirTocEntry {int fileProperties; int filenameLength; scalar_t__* filename; int /*<<< orphan*/  fileLBA; int /*<<< orphan*/  fileSize; } ;
struct TocEntry {int fileProperties; scalar_t__* filename; int /*<<< orphan*/  fileLBA; int /*<<< orphan*/  fileSize; } ;
struct TYPE_2__ {int filesystemType; } ;

/* Variables and functions */
 TYPE_1__ CDVolDesc ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  strtok (scalar_t__*,char*) ; 

void TocEntryCopy(struct TocEntry *tocEntry, struct dirTocEntry *internalTocEntry)
{
    int i;
    int filenamelen;

    tocEntry->fileSize = internalTocEntry->fileSize;
    tocEntry->fileLBA = internalTocEntry->fileLBA;
    tocEntry->fileProperties = internalTocEntry->fileProperties;

    if (CDVolDesc.filesystemType == 2) {
        // This is a Joliet Filesystem, so use Unicode to ISO string copy
        filenamelen = internalTocEntry->filenameLength / 2;

        for (i = 0; i < filenamelen; i++)
            tocEntry->filename[i] = internalTocEntry->filename[(i << 1) + 1];
    } else {
        filenamelen = internalTocEntry->filenameLength;

        // use normal string copy
        strncpy(tocEntry->filename, internalTocEntry->filename, 128);
    }

    tocEntry->filename[filenamelen] = 0;

    if (!(tocEntry->fileProperties & 0x02)) {
        // strip the ;1 from the filename (if it's there)
        strtok(tocEntry->filename, ";");
    }
}