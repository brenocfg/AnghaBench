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
typedef  int /*<<< orphan*/  SVnodeObj ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vnodeList ; 
 int /*<<< orphan*/ * vnodeOpenMeterObjFile (int) ; 
 int /*<<< orphan*/  vnodeUpdateVnodeFileHeader (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int vnodeSaveVnodeInfo(int vnode) {
  FILE *     fp;
  SVnodeObj *pVnode = &vnodeList[vnode];

  fp = vnodeOpenMeterObjFile(vnode);
  if (fp == NULL) return -1;

  vnodeUpdateVnodeFileHeader(fp, pVnode);
  /* vnodeUpdateFileCheckSum(fp); */
  fclose(fp);

  return 0;
}