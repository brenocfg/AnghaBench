#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct _iop_thread {int priority; int stacksize; scalar_t__ option; void* thread; int /*<<< orphan*/  attr; } ;
struct TYPE_7__ {char* cache; scalar_t__ cache_size; scalar_t__ cache_offset; scalar_t__ sector_num; scalar_t__ sector_start; scalar_t__ path_depth; int /*<<< orphan*/  valid; int /*<<< orphan*/  pathname; } ;
struct TYPE_6__ {int /*<<< orphan*/  datapattern; int /*<<< orphan*/  spindlctrl; scalar_t__ trycount; } ;
struct TYPE_5__ {char* name; int version; char* desc; int /*<<< orphan*/ * ops; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddDrv (TYPE_1__*) ; 
 scalar_t__ AllocSysMemory (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ CDVD_Thread ; 
 TYPE_3__ CachedDirInfo ; 
 int CreateThread (struct _iop_thread*) ; 
 int /*<<< orphan*/  DelDrv (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IOP_DT_FS ; 
 int MAX_DIR_CACHE_SECTORS ; 
 int MODULE_NO_RESIDENT_END ; 
 int MODULE_RESIDENT_END ; 
 int /*<<< orphan*/  SCECdSecS2048 ; 
 int /*<<< orphan*/  SCECdSpinStm ; 
 int /*<<< orphan*/  StartThread (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TH_C ; 
 TYPE_2__ cdReadMode ; 
 TYPE_1__ file_driver ; 
 int /*<<< orphan*/  filedriver_ops ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int _start(int argc, char **argv)
{
    int i;
    struct _iop_thread param;
    int th;

    // Initialise the directory cache
    strcpy(CachedDirInfo.pathname, "");  // The pathname of the cached directory
    CachedDirInfo.valid = FALSE;         // Cache is not valid
    CachedDirInfo.path_depth = 0;        // 0 = root)
    CachedDirInfo.sector_start = 0;      // The start sector (LBA) of the cached directory
    CachedDirInfo.sector_num = 0;        // The total size of the directory (in sectors)
    CachedDirInfo.cache_offset = 0;      // The offset from sector_start of the cached area
    CachedDirInfo.cache_size = 0;        // The size of the cached directory area (in sectors)

    if (CachedDirInfo.cache == NULL)
        CachedDirInfo.cache = (char *)AllocSysMemory(0, MAX_DIR_CACHE_SECTORS * 2048, NULL);


    // setup the cdReadMode structure
    cdReadMode.trycount = 0;
    cdReadMode.spindlctrl = SCECdSpinStm;
    cdReadMode.datapattern = SCECdSecS2048;

    // setup the file_driver structure
    file_driver.name = "cdfs";
    file_driver.type = IOP_DT_FS;
    file_driver.version = 1;
    file_driver.desc = "CDVD Filedriver";
    file_driver.ops = &filedriver_ops;

    DelDrv("cdfs");
    AddDrv(&file_driver);

    param.attr = TH_C;
    param.thread = (void *)CDVD_Thread;
    param.priority = 40;
    param.stacksize = 0x8000;
    param.option = 0;

    th = CreateThread(&param);

    if (th > 0) {
        StartThread(th, NULL);
        return MODULE_RESIDENT_END;
    } else
        return MODULE_NO_RESIDENT_END;
}