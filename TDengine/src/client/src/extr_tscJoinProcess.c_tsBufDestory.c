#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  payload; } ;
struct TYPE_6__ {int /*<<< orphan*/  rawBuf; } ;
struct TYPE_8__ {int /*<<< orphan*/  path; scalar_t__ autoDelete; int /*<<< orphan*/  f; TYPE_2__ block; int /*<<< orphan*/  pData; TYPE_1__ tsData; int /*<<< orphan*/  assistBuf; } ;
typedef  TYPE_3__ STSBuf ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  tfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

void tsBufDestory(STSBuf* pTSBuf) {
  if (pTSBuf == NULL) {
    return;
  }

  tfree(pTSBuf->assistBuf);
  tfree(pTSBuf->tsData.rawBuf);

  tfree(pTSBuf->pData);
  tfree(pTSBuf->block.payload);

  fclose(pTSBuf->f);

  if (pTSBuf->autoDelete) {
    unlink(pTSBuf->path);
  }

  free(pTSBuf);
}