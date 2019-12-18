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
struct stat {int /*<<< orphan*/  st_size; } ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  __off_t ;
struct TYPE_3__ {int fileID; int headerFd; int dataFd; int lastFd; int /*<<< orphan*/ * pDataFileData; int /*<<< orphan*/  defaultMappingSize; int /*<<< orphan*/ * pHeaderFileData; int /*<<< orphan*/  headFileSize; int /*<<< orphan*/  dataFilePath; int /*<<< orphan*/  dtFileMappingOffset; int /*<<< orphan*/  lastFileSize; int /*<<< orphan*/  lastFilePath; int /*<<< orphan*/  dataFileSize; int /*<<< orphan*/  headerFilePath; } ;
typedef  TYPE_1__ SQueryFileInfo ;
typedef  int /*<<< orphan*/  SQInfo ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_DATA_FILE_MMAP_WINDOW_SIZE ; 
 int /*<<< orphan*/  MADV_SEQUENTIAL ; 
 int /*<<< orphan*/ * MAP_FAILED ; 
 int MAP_POPULATE ; 
 int MAP_PRIVATE ; 
 int MAP_SHARED ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  VALIDFD (int) ; 
 int /*<<< orphan*/  dError (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fileHandleHashList ; 
 int madvise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,...) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosAddStrHash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ taosGetStrHashData (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tclose (int) ; 

__attribute__((used)) static int32_t vnodeOpenVnodeDBFiles(SQInfo *pQInfo, SQueryFileInfo *pVnodeFiles, int32_t fid, int32_t vnodeId,
                                     char *fileName, char *prefix) {
  __off_t size = 0;

  pVnodeFiles->fileID = fid;
  pVnodeFiles->defaultMappingSize = DEFAULT_DATA_FILE_MMAP_WINDOW_SIZE;

  snprintf(pVnodeFiles->headerFilePath, 256, "%s%s", prefix, fileName);

#if 1
  pVnodeFiles->headerFd = open(pVnodeFiles->headerFilePath, O_RDONLY);
#else
  int32_t *val = (int32_t *)taosGetStrHashData(fileHandleHashList, pVnodeFiles->headerFilePath);
  if (val == NULL) {
    pVnodeFiles->headerFd = open(pVnodeFiles->headerFilePath, O_RDONLY);
    taosAddStrHash(fileHandleHashList, pVnodeFiles->headerFilePath, (char *)&pVnodeFiles->headerFd);
  } else {
    pVnodeFiles->headerFd = *val;
  }
#endif

  if (!VALIDFD(pVnodeFiles->headerFd)) {
    dError("QInfo:%p failed open header file:%s reason:%s", pQInfo, pVnodeFiles->headerFilePath, strerror(errno));
    goto _clean;
  }

  struct stat fstat;
  if (stat(pVnodeFiles->headerFilePath, &fstat) < 0) return -1;
  pVnodeFiles->headFileSize = fstat.st_size;
  size = fstat.st_size;

  pVnodeFiles->pHeaderFileData = mmap(NULL, size, PROT_READ, MAP_SHARED, pVnodeFiles->headerFd, 0);
  if (pVnodeFiles->pHeaderFileData == MAP_FAILED) {
    dError("QInfo:%p failed to map header file:%s, %s", pQInfo, pVnodeFiles->headerFilePath, strerror(errno));
    goto _clean;
  }

  /* even the advise failed, continue.. */
  if (madvise(pVnodeFiles->pHeaderFileData, size, MADV_SEQUENTIAL) == -1) {
    dError("QInfo:%p failed to advise kernel the usage of header files, reason:%s", pQInfo, strerror(errno));
  }

  snprintf(pVnodeFiles->dataFilePath, 256, "%sv%df%d.data", prefix, vnodeId, fid);
  snprintf(pVnodeFiles->lastFilePath, 256, "%sv%df%d.last", prefix, vnodeId, fid);

#if 1
  pVnodeFiles->dataFd = open(pVnodeFiles->dataFilePath, O_RDONLY);
  pVnodeFiles->lastFd = open(pVnodeFiles->lastFilePath, O_RDONLY);
#else
  val = (int32_t *)taosGetStrHashData(fileHandleHashList, pVnodeFiles->dataFilePath);
  if (val == NULL) {
    pVnodeFiles->dataFd = open(pVnodeFiles->dataFilePath, O_RDONLY);
    taosAddStrHash(fileHandleHashList, pVnodeFiles->dataFilePath, (char *)&pVnodeFiles->dataFd);
  } else {
    pVnodeFiles->dataFd = *val;
  }
#endif

  if (!VALIDFD(pVnodeFiles->dataFd)) {
    dError("QInfo:%p failed to open data file:%s, reason:%s", pQInfo, pVnodeFiles->dataFilePath, strerror(errno));
    goto _clean;
  }

  if (!VALIDFD(pVnodeFiles->lastFd)) {
    dError("QInfo:%p failed to open last file:%s, reason:%s", pQInfo, pVnodeFiles->lastFilePath, strerror(errno));
    goto _clean;
  }

  if (stat(pVnodeFiles->dataFilePath, &fstat) < 0) return -1;
  pVnodeFiles->dataFileSize = fstat.st_size;

  if (stat(pVnodeFiles->lastFilePath, &fstat) < 0) return -1;
  pVnodeFiles->lastFileSize = fstat.st_size;

#if DEFAULT_IO_ENGINE == IO_ENGINE_MMAP
  /* enforce kernel to preload data when the file is mapping */
  pVnodeFiles->pDataFileData = mmap(NULL, pVnodeFiles->defaultMappingSize, PROT_READ, MAP_PRIVATE | MAP_POPULATE,
                                    pVnodeFiles->dataFd, pVnodeFiles->dtFileMappingOffset);
  if (pVnodeFiles->pDataFileData == MAP_FAILED) {
    dError("QInfo:%p failed to map data file:%s, %s", pQInfo, pVnodeFiles->dataFilePath, strerror(errno));
    goto _clean;
  }

  /* advise kernel the usage of mmaped data */
  if (madvise(pVnodeFiles->pDataFileData, pVnodeFiles->defaultMappingSize, MADV_SEQUENTIAL) == -1) {
    dError("QInfo:%p failed to advise kernel the usage of data file:%s, reason:%s", pQInfo, pVnodeFiles->dataFilePath,
           strerror(errno));
  }
#endif

  return 0;

_clean:
  if (pVnodeFiles->pHeaderFileData != MAP_FAILED && pVnodeFiles->pDataFileData != NULL) {
    munmap(pVnodeFiles->pHeaderFileData, pVnodeFiles->headFileSize);
    pVnodeFiles->pHeaderFileData = NULL;
  }

#if DEFAULT_IO_ENGINE == IO_ENGINE_MMAP
  if (pVnodeFiles->pDataFileData != MAP_FAILED && pVnodeFiles->pDataFileData != NULL) {
    munmap(pVnodeFiles->pDataFileData, pVnodeFiles->defaultMappingSize);
    pVnodeFiles->pDataFileData = NULL;
  }
#endif

  tclose(pVnodeFiles->headerFd);
  tclose(pVnodeFiles->dataFd);
  tclose(pVnodeFiles->lastFd);
  return -1;
}