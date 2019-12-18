#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* pz; int /*<<< orphan*/  dKey; int /*<<< orphan*/  i64Key; } ;
struct TYPE_8__ {struct TYPE_8__** pForward; TYPE_2__ key; } ;
typedef  TYPE_3__ tSkipListNode ;
struct TYPE_6__ {TYPE_3__** pForward; } ;
struct TYPE_9__ {int nLevel; int keyType; TYPE_1__ pHead; } ;
typedef  TYPE_4__ tSkipList ;
typedef  int int32_t ;
typedef  int int16_t ;

/* Variables and functions */
#define  TSDB_DATA_TYPE_BIGINT 133 
#define  TSDB_DATA_TYPE_BINARY 132 
#define  TSDB_DATA_TYPE_DOUBLE 131 
#define  TSDB_DATA_TYPE_INT 130 
#define  TSDB_DATA_TYPE_SMALLINT 129 
#define  TSDB_DATA_TYPE_TINYINT 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stdout ; 

void tSkipListPrint(tSkipList *pSkipList, int16_t nlevel) {
  if (pSkipList == NULL || pSkipList->nLevel < nlevel || nlevel <= 0) {
    return;
  }

  tSkipListNode *p = pSkipList->pHead.pForward[nlevel - 1];
  int32_t        id = 1;
  while (p) {
    switch (pSkipList->keyType) {
      case TSDB_DATA_TYPE_INT:
      case TSDB_DATA_TYPE_SMALLINT:
      case TSDB_DATA_TYPE_TINYINT:
      case TSDB_DATA_TYPE_BIGINT:
        fprintf(stdout, "%d: %lld \n", id++, p->key.i64Key);
        break;
      case TSDB_DATA_TYPE_BINARY:
        fprintf(stdout, "%d: %s \n", id++, p->key.pz);
        break;
      case TSDB_DATA_TYPE_DOUBLE:
        fprintf(stdout, "%d: %lf \n", id++, p->key.dKey);
        break;
      default:
        fprintf(stdout, "\n");
    }
    p = p->pForward[nlevel - 1];
  }
}