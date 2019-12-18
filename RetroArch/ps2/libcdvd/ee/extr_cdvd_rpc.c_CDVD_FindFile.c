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

/* Variables and functions */
 int /*<<< orphan*/  CDVD_FINDFILE ; 
 int /*<<< orphan*/  SifCallRpc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cd0 ; 
 int /*<<< orphan*/  cdvd_inited ; 
 int /*<<< orphan*/  memcpy (struct TocEntry*,int*,int) ; 
 int* sbuff ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

int CDVD_FindFile(const char *fname, struct TocEntry *tocEntry)
{
    if (!cdvd_inited)
        return -1;

    strncpy((char *)&sbuff, fname, 1024);

    SifCallRpc(&cd0, CDVD_FINDFILE, 0, (void *)(&sbuff[0]), 1024, (void *)(&sbuff[0]), sizeof(struct TocEntry) + 1024, 0, 0);

    memcpy(tocEntry, &sbuff[256], sizeof(struct TocEntry));

    return sbuff[0];
}