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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  TSKEY ;
typedef  int /*<<< orphan*/  SQLFunctionCtx ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_DATA_ALL_NEEDED ; 

__attribute__((used)) static int32_t data_req_load_info(SQLFunctionCtx *pCtx, TSKEY start, TSKEY end, int32_t colId, int32_t blockStatus) {
  return BLK_DATA_ALL_NEEDED;
}