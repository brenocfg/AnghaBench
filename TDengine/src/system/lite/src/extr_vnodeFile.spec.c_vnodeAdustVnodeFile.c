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
struct TYPE_4__ {size_t precision; int daysPerFile; } ;
struct TYPE_5__ {int fileId; int numOfFiles; int maxFiles; int /*<<< orphan*/  vnode; TYPE_1__ cfg; } ;
typedef  TYPE_2__ SVnodeObj ;

/* Variables and functions */
 int taosGetTimestamp (size_t) ; 
 int* tsMsPerDay ; 
 int /*<<< orphan*/  vnodeRemoveFile (int /*<<< orphan*/ ,int) ; 

void vnodeAdustVnodeFile(SVnodeObj *pVnode) {
  // Retention policy here
  int fileId = pVnode->fileId - pVnode->numOfFiles + 1;
  int cfile = taosGetTimestamp(pVnode->cfg.precision)/pVnode->cfg.daysPerFile/tsMsPerDay[pVnode->cfg.precision];
  while (fileId <= cfile - pVnode->maxFiles) {
    vnodeRemoveFile(pVnode->vnode, fileId);
    pVnode->numOfFiles--;
    fileId++;
  }
}