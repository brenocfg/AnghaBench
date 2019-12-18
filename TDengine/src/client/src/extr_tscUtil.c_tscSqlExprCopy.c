#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  size_t int32_t ;
typedef  size_t int16_t ;
struct TYPE_6__ {scalar_t__ uid; size_t numOfParams; int /*<<< orphan*/ * param; } ;
struct TYPE_5__ {int numOfAlloc; size_t numOfExprs; TYPE_4__* pExprs; } ;
typedef  TYPE_1__ SSqlExprInfo ;
typedef  int /*<<< orphan*/  SSqlExpr ;

/* Variables and functions */
 TYPE_4__* malloc (int) ; 
 int /*<<< orphan*/  tVariantAssign (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void tscSqlExprCopy(SSqlExprInfo* dst, const SSqlExprInfo* src, uint64_t tableuid) {
  if (src == NULL) {
    return;
  }

  *dst = *src;

  dst->pExprs = malloc(sizeof(SSqlExpr) * dst->numOfAlloc);
  int16_t num = 0;
  for (int32_t i = 0; i < src->numOfExprs; ++i) {
    if (src->pExprs[i].uid == tableuid) {
      dst->pExprs[num++] = src->pExprs[i];
    }
  }

  dst->numOfExprs = num;
  for (int32_t i = 0; i < dst->numOfExprs; ++i) {
    for (int32_t j = 0; j < src->pExprs[i].numOfParams; ++j) {
      tVariantAssign(&dst->pExprs[i].param[j], &src->pExprs[i].param[j]);
    }
  }
}