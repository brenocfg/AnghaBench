#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int numOfOutputCols; int numOfHiddenCols; } ;
struct TYPE_4__ {TYPE_3__ fieldsInfo; } ;
struct TYPE_5__ {TYPE_1__ cmd; struct TYPE_5__* signature; } ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  TYPE_2__ SSqlObj ;
typedef  TYPE_3__ SFieldInfo ;

/* Variables and functions */

int taos_num_fields(TAOS_RES *res) {
  SSqlObj *pSql = (SSqlObj *)res;
  if (pSql == NULL || pSql->signature != pSql) return 0;

  SFieldInfo *pFieldsInfo = &pSql->cmd.fieldsInfo;

  return (pFieldsInfo->numOfOutputCols - pFieldsInfo->numOfHiddenCols);
}