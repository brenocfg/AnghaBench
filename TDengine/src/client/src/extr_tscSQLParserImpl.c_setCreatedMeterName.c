#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ n; } ;
struct TYPE_8__ {TYPE_1__* pCreateTableInfo; } ;
struct TYPE_7__ {int existCheck; TYPE_3__ name; } ;
typedef  TYPE_2__ SSqlInfo ;
typedef  TYPE_3__ SSQLToken ;

/* Variables and functions */

void setCreatedMeterName(SSqlInfo *pInfo, SSQLToken *pMeterName, SSQLToken *pIfNotExists) {
  pInfo->pCreateTableInfo->name = *pMeterName;
  pInfo->pCreateTableInfo->existCheck = (pIfNotExists->n != 0);
}