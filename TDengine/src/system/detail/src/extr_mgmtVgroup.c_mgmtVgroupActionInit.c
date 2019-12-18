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

/* Variables and functions */
 size_t SDB_TYPE_AFTER_BATCH_UPDATE ; 
 size_t SDB_TYPE_BATCH_UPDATE ; 
 size_t SDB_TYPE_BEFORE_BATCH_UPDATE ; 
 size_t SDB_TYPE_DECODE ; 
 size_t SDB_TYPE_DELETE ; 
 size_t SDB_TYPE_DESTROY ; 
 size_t SDB_TYPE_ENCODE ; 
 size_t SDB_TYPE_INSERT ; 
 size_t SDB_TYPE_RESET ; 
 size_t SDB_TYPE_UPDATE ; 
 int /*<<< orphan*/  mgmtVgroupActionAfterBatchUpdate ; 
 int /*<<< orphan*/  mgmtVgroupActionBatchUpdate ; 
 int /*<<< orphan*/  mgmtVgroupActionBeforeBatchUpdate ; 
 int /*<<< orphan*/  mgmtVgroupActionDecode ; 
 int /*<<< orphan*/  mgmtVgroupActionDelete ; 
 int /*<<< orphan*/  mgmtVgroupActionDestroy ; 
 int /*<<< orphan*/  mgmtVgroupActionEncode ; 
 int /*<<< orphan*/ * mgmtVgroupActionFp ; 
 int /*<<< orphan*/  mgmtVgroupActionInsert ; 
 int /*<<< orphan*/  mgmtVgroupActionReset ; 
 int /*<<< orphan*/  mgmtVgroupActionUpdate ; 

void mgmtVgroupActionInit() {
  mgmtVgroupActionFp[SDB_TYPE_INSERT] = mgmtVgroupActionInsert;
  mgmtVgroupActionFp[SDB_TYPE_DELETE] = mgmtVgroupActionDelete;
  mgmtVgroupActionFp[SDB_TYPE_UPDATE] = mgmtVgroupActionUpdate;
  mgmtVgroupActionFp[SDB_TYPE_ENCODE] = mgmtVgroupActionEncode;
  mgmtVgroupActionFp[SDB_TYPE_DECODE] = mgmtVgroupActionDecode;
  mgmtVgroupActionFp[SDB_TYPE_BEFORE_BATCH_UPDATE] = mgmtVgroupActionBeforeBatchUpdate;
  mgmtVgroupActionFp[SDB_TYPE_BATCH_UPDATE] = mgmtVgroupActionBatchUpdate;
  mgmtVgroupActionFp[SDB_TYPE_AFTER_BATCH_UPDATE] = mgmtVgroupActionAfterBatchUpdate;
  mgmtVgroupActionFp[SDB_TYPE_RESET] = mgmtVgroupActionReset;
  mgmtVgroupActionFp[SDB_TYPE_DESTROY] = mgmtVgroupActionDestroy;
}