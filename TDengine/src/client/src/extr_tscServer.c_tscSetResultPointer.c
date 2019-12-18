#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int int16_t ;
struct TYPE_14__ {scalar_t__ order; } ;
struct TYPE_13__ {int numOfOutputCols; } ;
struct TYPE_17__ {TYPE_2__ order; TYPE_1__ fieldsInfo; } ;
struct TYPE_16__ {int code; int* bytes; int numOfRows; scalar_t__ data; scalar_t__* tsrow; } ;
struct TYPE_15__ {int bytes; } ;
typedef  TYPE_3__ TAOS_FIELD ;
typedef  TYPE_4__ SSqlRes ;
typedef  TYPE_5__ SSqlCmd ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_SUCCESS ; 
 scalar_t__ TSQL_SO_DESC ; 
 scalar_t__ tscCreateResPointerInfo (TYPE_5__*,TYPE_4__*) ; 
 TYPE_3__* tscFieldInfoGetField (TYPE_5__*,int) ; 
 int tscFieldInfoGetOffset (TYPE_5__*,int) ; 

__attribute__((used)) static int tscSetResultPointer(SSqlCmd *pCmd, SSqlRes *pRes) {
  if (tscCreateResPointerInfo(pCmd, pRes) != TSDB_CODE_SUCCESS) {
    return pRes->code;
  }

  for (int i = 0; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
    TAOS_FIELD *pField = tscFieldInfoGetField(pCmd, i);
    int16_t     offset = tscFieldInfoGetOffset(pCmd, i);

    pRes->bytes[i] = pField->bytes;
    if (pCmd->order.order == TSQL_SO_DESC) {
      pRes->bytes[i] = -pRes->bytes[i];
      pRes->tsrow[i] = ((pRes->data + offset * pRes->numOfRows) + (pRes->numOfRows - 1) * pField->bytes);
    } else {
      pRes->tsrow[i] = (pRes->data + offset * pRes->numOfRows);
    }
  }

  return 0;
}