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
struct TYPE_7__ {int numOfCols; TYPE_2__* pSchema; scalar_t__* colOffset; } ;
typedef  TYPE_1__ tTagSchema ;
typedef  int int32_t ;
struct TYPE_8__ {scalar_t__ bytes; } ;
typedef  TYPE_2__ SSchema ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 

tTagSchema *tCreateTagSchema(SSchema *pSchema, int32_t numOfTagCols) {
  if (numOfTagCols == 0 || pSchema == NULL) {
    return NULL;
  }

  tTagSchema *pTagSchema =
      (tTagSchema *)calloc(1, sizeof(tTagSchema) + numOfTagCols * sizeof(int32_t) + sizeof(SSchema) * numOfTagCols);

  pTagSchema->colOffset[0] = 0;
  pTagSchema->numOfCols = numOfTagCols;
  for (int32_t i = 1; i < numOfTagCols; ++i) {
    pTagSchema->colOffset[i] = (pTagSchema->colOffset[i - 1] + pSchema[i - 1].bytes);
  }

  pTagSchema->pSchema = (SSchema *)&(pTagSchema->colOffset[numOfTagCols]);
  memcpy(pTagSchema->pSchema, pSchema, sizeof(SSchema) * numOfTagCols);
  return pTagSchema;
}