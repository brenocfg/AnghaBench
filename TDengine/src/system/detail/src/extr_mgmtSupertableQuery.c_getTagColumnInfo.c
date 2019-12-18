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
typedef  size_t int32_t ;
struct TYPE_8__ {scalar_t__ bytes; scalar_t__ type; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {size_t numOfTags; TYPE_1__* pTagSchema; } ;
struct TYPE_6__ {scalar_t__ bytes; scalar_t__ type; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ SSyntaxTreeFilterSupporter ;
typedef  TYPE_3__ SSchema ;

/* Variables and functions */
 size_t TSDB_TBNAME_COLUMN_INDEX ; 
 int /*<<< orphan*/  TSQL_TBNAME_L ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void getTagColumnInfo(SSyntaxTreeFilterSupporter* pSupporter, SSchema* pSchema, int32_t* index,
                             int32_t* offset) {
  *index = 0;
  *offset = 0;

  // filter on table name(TBNAME)
  if (strcasecmp(pSchema->name, TSQL_TBNAME_L) == 0) {
    *index = TSDB_TBNAME_COLUMN_INDEX;
    *offset = TSDB_TBNAME_COLUMN_INDEX;
    return;
  }

  while ((*index) < pSupporter->numOfTags) {
    if (pSupporter->pTagSchema[*index].bytes == pSchema->bytes &&
        pSupporter->pTagSchema[*index].type == pSchema->type &&
        strcmp(pSupporter->pTagSchema[*index].name, pSchema->name) == 0) {
      break;
    } else {
      (*offset) += pSupporter->pTagSchema[(*index)++].bytes;
    }
  }
}