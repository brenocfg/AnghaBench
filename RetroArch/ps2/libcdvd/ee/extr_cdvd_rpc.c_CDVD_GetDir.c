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
struct TocEntry {int dummy; } ;
typedef  enum CDVD_getMode { ____Placeholder_CDVD_getMode } CDVD_getMode ;

/* Variables and functions */
 int /*<<< orphan*/  CDVD_GETDIR ; 
 int /*<<< orphan*/  SifCallRpc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SifWriteBackDCache (struct TocEntry*,unsigned int) ; 
 int /*<<< orphan*/  cd0 ; 
 int /*<<< orphan*/  cdvd_inited ; 
 unsigned int* sbuff ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

int CDVD_GetDir(const char *pathname, const char *extensions, enum CDVD_getMode getMode, struct TocEntry tocEntry[], unsigned int req_entries, char *new_pathname)
{
    unsigned int num_entries;

    if (!cdvd_inited)
        return -1;

    // copy the requested pathname to the rpc buffer
    strncpy((char *)sbuff, pathname, 1023);

    // copy in the extension list to the rpc buffer
    if (extensions == NULL) {
        // Can't copy in the extension list since there isnt one, so just null the string in the rpc buffer
        sbuff[1024 / 4] = 0;
    } else {
        strncpy((char *)&sbuff[1024 / 4], extensions, 127);
    }

    sbuff[1152 / 4] = getMode;

    sbuff[1156 / 4] = (int)tocEntry;

    sbuff[1160 / 4] = req_entries;

    SifWriteBackDCache(tocEntry, req_entries * sizeof(struct TocEntry));

    // This will get the directory contents, and fill tocEntry via DMA
    SifCallRpc(&cd0, CDVD_GETDIR, 0, (void *)(&sbuff[0]), 1024 + 128 + 4 + 4 + 4, (void *)(&sbuff[0]), 4 + 1024, 0, 0);

    num_entries = sbuff[0];

    if (new_pathname != NULL)
        strncpy(new_pathname, (char *)&sbuff[1], 1023);

    return (num_entries);
}