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
typedef  int int32_t ;
struct TYPE_5__ {int numOfFiles; TYPE_1__* pHeaderFiles; } ;
struct TYPE_4__ {int fileID; } ;
typedef  TYPE_2__ SQueryRuntimeEnv ;

/* Variables and functions */
 int TSQL_SO_ASC ; 
 int TSQL_SO_DESC ; 

int32_t vnodeGetVnodeHeaderFileIdx(int32_t *fid, SQueryRuntimeEnv *pRuntimeEnv, int32_t order) {
  if (pRuntimeEnv->numOfFiles == 0) {
    return -1;
  }

  /* set the initial file for current query */
  if (order == TSQL_SO_ASC && *fid < pRuntimeEnv->pHeaderFiles[0].fileID) {
    *fid = pRuntimeEnv->pHeaderFiles[0].fileID;
    return 0;
  } else if (order == TSQL_SO_DESC && *fid > pRuntimeEnv->pHeaderFiles[pRuntimeEnv->numOfFiles - 1].fileID) {
    *fid = pRuntimeEnv->pHeaderFiles[pRuntimeEnv->numOfFiles - 1].fileID;
    return pRuntimeEnv->numOfFiles - 1;
  }

  int32_t numOfFiles = pRuntimeEnv->numOfFiles;

  if (order == TSQL_SO_DESC && *fid > pRuntimeEnv->pHeaderFiles[numOfFiles - 1].fileID) {
    *fid = pRuntimeEnv->pHeaderFiles[numOfFiles - 1].fileID;
    return numOfFiles - 1;
  }

  if (order == TSQL_SO_ASC) {
    int32_t i = 0;
    int32_t step = 1;

    while (i<numOfFiles && * fid> pRuntimeEnv->pHeaderFiles[i].fileID) {
      i += step;
    }

    if (i < numOfFiles && *fid <= pRuntimeEnv->pHeaderFiles[i].fileID) {
      *fid = pRuntimeEnv->pHeaderFiles[i].fileID;
      return i;
    } else {
      return -1;
    }
  } else {
    int32_t i = numOfFiles - 1;
    int32_t step = -1;

    while (i >= 0 && *fid < pRuntimeEnv->pHeaderFiles[i].fileID) {
      i += step;
    }

    if (i >= 0 && *fid >= pRuntimeEnv->pHeaderFiles[i].fileID) {
      *fid = pRuntimeEnv->pHeaderFiles[i].fileID;
      return i;
    } else {
      return -1;
    }
  }
}