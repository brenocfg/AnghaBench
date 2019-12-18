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
struct TYPE_3__ {int /*<<< orphan*/  numOfFiles; int /*<<< orphan*/  fileId; int /*<<< orphan*/  lastKeyOnFile; int /*<<< orphan*/  version; int /*<<< orphan*/  lastRemove; int /*<<< orphan*/  lastCreate; } ;
typedef  TYPE_1__ SVnodeObj ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int TSDB_FILE_HEADER_LEN ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void vnodeUpdateVnodeFileHeader(FILE *fp, SVnodeObj *pVnode) {
  fseek(fp, TSDB_FILE_HEADER_LEN * 1 / 4, SEEK_SET);

#ifdef _TD_ARM_32_
  fprintf(fp, "%lld %lld %lld ", pVnode->lastCreate, pVnode->lastRemove, pVnode->version);
  fprintf(fp, "%lld %d %d ", pVnode->lastKeyOnFile, pVnode->fileId, pVnode->numOfFiles);
#else
  fprintf(fp, "%ld %ld %ld ", pVnode->lastCreate, pVnode->lastRemove, pVnode->version);
  fprintf(fp, "%ld %d %d ", pVnode->lastKeyOnFile, pVnode->fileId, pVnode->numOfFiles);
#endif  
}