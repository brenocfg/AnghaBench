#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int numOfCols; int maxCapacity; TYPE_2__* pFields; scalar_t__* colOffset; } ;
typedef  TYPE_1__ tColModel ;
typedef  int int32_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_8__ {scalar_t__ bytes; } ;
typedef  TYPE_2__ SSchema ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 

tColModel *tColModelCreate(SSchema *field, int32_t numOfCols, int32_t maxCapacity) {
  tColModel *pSchema =
      (tColModel *)calloc(1, sizeof(tColModel) + numOfCols * sizeof(SSchema) + numOfCols * sizeof(int16_t));
  if (pSchema == NULL) {
    return NULL;
  }

  pSchema->pFields = (SSchema *)(&pSchema[1]);
  memcpy(pSchema->pFields, field, sizeof(SSchema) * numOfCols);

  pSchema->colOffset = (int16_t *)(&pSchema->pFields[numOfCols]);
  pSchema->colOffset[0] = 0;
  for (int32_t i = 1; i < numOfCols; ++i) {
    pSchema->colOffset[i] = pSchema->colOffset[i - 1] + pSchema->pFields[i - 1].bytes;
  }

  pSchema->numOfCols = numOfCols;
  pSchema->maxCapacity = maxCapacity;

  return pSchema;
}