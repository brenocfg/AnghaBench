#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  TSKEY ;
typedef  int /*<<< orphan*/  SQLFunctionCtx ;

/* Variables and functions */
 scalar_t__ BLK_DATA_FILEDS_NEEDED ; 
 scalar_t__ BLK_DATA_NO_NEEDED ; 
 scalar_t__ PRIMARYKEY_TIMESTAMP_COL_INDEX ; 

int32_t count_load_data_info(SQLFunctionCtx *pCtx, TSKEY start, TSKEY end, int32_t colId, int32_t blockStatus) {
  if (colId == PRIMARYKEY_TIMESTAMP_COL_INDEX) {
    return BLK_DATA_NO_NEEDED;
  } else {
    return BLK_DATA_FILEDS_NEEDED;
  }
}