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
struct TYPE_8__ {TYPE_1__* pNode; } ;
typedef  TYPE_3__ tSQLExprItem ;
struct TYPE_9__ {int /*<<< orphan*/  n; int /*<<< orphan*/  z; void* type; } ;
struct TYPE_7__ {int /*<<< orphan*/  nLen; int /*<<< orphan*/  pz; } ;
struct TYPE_6__ {scalar_t__ nSQLOptr; TYPE_2__ val; TYPE_4__ colInfo; } ;
typedef  TYPE_4__ SSQLToken ;

/* Variables and functions */
 void* TK_ID ; 
 scalar_t__ TK_STRING ; 
 int /*<<< orphan*/  strdequote (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void extractColumnNameFromString(tSQLExprItem* pItem) {
  if (pItem->pNode->nSQLOptr == TK_STRING) {
    pItem->pNode->val.nLen = strdequote(pItem->pNode->val.pz);
    pItem->pNode->nSQLOptr = TK_ID;

    SSQLToken* pIdToken = &pItem->pNode->colInfo;
    pIdToken->type = TK_ID;
    pIdToken->z = pItem->pNode->val.pz;
    pIdToken->n = pItem->pNode->val.nLen;
  }
}