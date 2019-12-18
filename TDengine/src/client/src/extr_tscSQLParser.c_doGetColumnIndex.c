#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
typedef  size_t int16_t ;
struct TYPE_11__ {TYPE_3__* pMeterMeta; } ;
struct TYPE_10__ {size_t numOfColumns; size_t numOfTags; } ;
struct TYPE_9__ {scalar_t__ n; int /*<<< orphan*/  z; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  SSqlCmd ;
typedef  TYPE_1__ SSchema ;
typedef  TYPE_2__ SSQLToken ;
typedef  TYPE_3__ SMeterMeta ;

/* Variables and functions */
 size_t COLUMN_INDEX_INITIAL_VAL ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* tsGetSchema (TYPE_3__*) ; 
 TYPE_4__* tscGetMeterMetaInfo (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int16_t doGetColumnIndex(SSqlCmd* pCmd, int32_t index, SSQLToken* pToken) {
  SMeterMeta* pMeterMeta = tscGetMeterMetaInfo(pCmd, index)->pMeterMeta;

  int32_t  numOfCols = pMeterMeta->numOfColumns + pMeterMeta->numOfTags;
  SSchema* pSchema = tsGetSchema(pMeterMeta);

  int16_t columnIndex = COLUMN_INDEX_INITIAL_VAL;

  for (int16_t i = 0; i < numOfCols; ++i) {
    if (pToken->n != strlen(pSchema[i].name)) {
      continue;
    }

    if (strncasecmp(pSchema[i].name, pToken->z, pToken->n) == 0) {
      columnIndex = i;
    }
  }

  return columnIndex;
}