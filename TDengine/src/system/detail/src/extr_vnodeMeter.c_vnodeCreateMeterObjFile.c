#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int32_t ;
struct TYPE_4__ {int maxSessions; } ;
struct TYPE_5__ {scalar_t__ meterIndex; TYPE_1__ cfg; } ;
typedef  int /*<<< orphan*/  TSCKSUM ;
typedef  int /*<<< orphan*/  SMeterObjHeader ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int TSDB_FILENAME_LEN ; 
 int /*<<< orphan*/  TSDB_FILE_HEADER_LEN ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  dError (char*,int,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (scalar_t__,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int,int) ; 
 int /*<<< orphan*/  taosCalcChecksumAppend (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tfree (scalar_t__) ; 
 char* tsDirectory ; 
 int /*<<< orphan*/  vnodeCreateFileHeader (int /*<<< orphan*/ *) ; 
 TYPE_2__* vnodeList ; 
 int /*<<< orphan*/  vnodeUpdateVnodeFileHeader (int /*<<< orphan*/ *,TYPE_2__*) ; 

int vnodeCreateMeterObjFile(int vnode) {
  FILE *  fp;
  char    fileName[TSDB_FILENAME_LEN];
  int32_t size;
  // SMeterObj *pObj;

  sprintf(fileName, "%s/vnode%d/meterObj.v%d", tsDirectory, vnode, vnode);
  fp = fopen(fileName, "w+");
  if (fp == NULL) {
    dError("failed to create vnode:%d file:%s", vnode, fileName);
    return -1;
  } else {
    vnodeCreateFileHeader(fp);
    vnodeUpdateVnodeFileHeader(fp, vnodeList + vnode);
    fseek(fp, TSDB_FILE_HEADER_LEN, SEEK_SET);

    size = sizeof(SMeterObjHeader) * vnodeList[vnode].cfg.maxSessions + sizeof(TSCKSUM);
    tfree(vnodeList[vnode].meterIndex);
    vnodeList[vnode].meterIndex = calloc(1, size);
    taosCalcChecksumAppend(0, (uint8_t *)(vnodeList[vnode].meterIndex), size);
    fwrite(vnodeList[vnode].meterIndex, size, 1, fp);

    fclose(fp);
  }

  return 0;
}