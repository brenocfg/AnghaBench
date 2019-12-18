#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_9__ {int /*<<< orphan*/  order; } ;
struct TYPE_11__ {int numOfVnodes; TYPE_1__ cur; } ;
struct TYPE_10__ {int vnode; int /*<<< orphan*/  ts; int /*<<< orphan*/  tag; } ;
typedef  TYPE_2__ STSElem ;
typedef  TYPE_3__ STSBuf ;

/* Variables and functions */
 int /*<<< orphan*/  TSQL_SO_ASC ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_2__ tsBufGetElem (TYPE_3__*) ; 
 scalar_t__ tsBufNextPos (TYPE_3__*) ; 
 int /*<<< orphan*/  tsBufResetPos (TYPE_3__*) ; 

void tsBufDisplay(STSBuf* pTSBuf) {
  printf("-------start of ts comp file-------\n");
  printf("number of vnode:%d\n", pTSBuf->numOfVnodes);

  int32_t old = pTSBuf->cur.order;
  pTSBuf->cur.order = TSQL_SO_ASC;

  tsBufResetPos(pTSBuf);

  while (tsBufNextPos(pTSBuf)) {
    STSElem elem = tsBufGetElem(pTSBuf);
    printf("%d-%lld-%lld\n", elem.vnode, elem.tag, elem.ts);
  }

  pTSBuf->cur.order = old;
  printf("-------end of ts comp file-------\n");
}