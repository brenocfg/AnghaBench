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
typedef  int /*<<< orphan*/  tVariantList ;
typedef  int /*<<< orphan*/  tFieldList ;
typedef  int int32_t ;
struct TYPE_7__ {int /*<<< orphan*/  metricName; int /*<<< orphan*/ * pTagVals; } ;
struct TYPE_6__ {int /*<<< orphan*/ * pTagColumns; int /*<<< orphan*/ * pColumns; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pSelect; TYPE_2__ usingInfo; TYPE_1__ colInfo; } ;
typedef  int /*<<< orphan*/  SSQLToken ;
typedef  int /*<<< orphan*/  SQuerySQL ;
typedef  TYPE_3__ SCreateTableSQL ;

/* Variables and functions */
#define  TSQL_CREATE_METER_FROM_METRIC 131 
#define  TSQL_CREATE_NORMAL_METER 130 
#define  TSQL_CREATE_NORMAL_METRIC 129 
#define  TSQL_CREATE_STREAM 128 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__* calloc (int,int) ; 

SCreateTableSQL *tSetCreateSQLElems(tFieldList *pCols, tFieldList *pTags, SSQLToken *pMetricName,
                                    tVariantList *pTagVals, SQuerySQL *pSelect, int32_t type) {
  SCreateTableSQL *pCreate = calloc(1, sizeof(SCreateTableSQL));

  switch (type) {
    case TSQL_CREATE_NORMAL_METER: {
      pCreate->colInfo.pColumns = pCols;
      assert(pTagVals == NULL && pTags == NULL);
      break;
    }
    case TSQL_CREATE_NORMAL_METRIC: {
      pCreate->colInfo.pColumns = pCols;
      pCreate->colInfo.pTagColumns = pTags;
      assert(pTagVals == NULL && pTags != NULL && pCols != NULL);
      break;
    }
    case TSQL_CREATE_METER_FROM_METRIC: {
      pCreate->usingInfo.pTagVals = pTagVals;
      pCreate->usingInfo.metricName = *pMetricName;
      break;
    }
    case TSQL_CREATE_STREAM: {
      pCreate->pSelect = pSelect;
      break;
    }
    default:
      assert(false);
  }

  return pCreate;
}