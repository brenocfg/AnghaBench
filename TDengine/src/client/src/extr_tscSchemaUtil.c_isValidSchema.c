#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct SSchema {scalar_t__ type; scalar_t__ bytes; int /*<<< orphan*/  name; } ;
typedef  size_t int32_t ;
struct TYPE_2__ {scalar_t__ nSize; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_COL_NAME_LEN ; 
 scalar_t__ TSDB_DATA_TYPE_BOOL ; 
 scalar_t__ TSDB_DATA_TYPE_TIMESTAMP ; 
 scalar_t__ TSDB_MAX_BINARY_LEN ; 
 size_t TSDB_MAX_BYTES_PER_ROW ; 
 int /*<<< orphan*/  VALIDNUMOFCOLS (size_t) ; 
 scalar_t__ strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* tDataTypeDesc ; 

bool isValidSchema(struct SSchema* pSchema, int32_t numOfCols) {
  if (!VALIDNUMOFCOLS(numOfCols)) {
    return false;
  }

  /* first column must be the timestamp, which is a primary key */
  if (pSchema[0].type != TSDB_DATA_TYPE_TIMESTAMP) {
    return false;
  }

  /* type is valid, length is valid */
  int32_t rowLen = 0;

  for (int32_t i = 0; i < numOfCols; ++i) {
    // 1. valid types
    if (pSchema[i].type > TSDB_DATA_TYPE_TIMESTAMP || pSchema[i].type < TSDB_DATA_TYPE_BOOL) {
      return false;
    }

    // 2. valid length for each type
    if (pSchema[i].type == TSDB_DATA_TYPE_TIMESTAMP) {
      if (pSchema[i].bytes > TSDB_MAX_BINARY_LEN) {
        return false;
      }
    } else {
      if (pSchema[i].bytes != tDataTypeDesc[pSchema[i].type].nSize) {
        return false;
      }
    }

    // 3. valid column names
    for (int32_t j = i + 1; j < numOfCols; ++j) {
      if (strncasecmp(pSchema[i].name, pSchema[j].name, TSDB_COL_NAME_LEN) == 0) {
        return false;
      }
    }

    rowLen += pSchema[i].bytes;
  }

  // valid total length
  return (rowLen <= TSDB_MAX_BYTES_PER_ROW);
}