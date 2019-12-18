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
 int /*<<< orphan*/  mgmtUserActionAfterBatchUpdate ; 
 int /*<<< orphan*/  mgmtUserActionBatchUpdate ; 
 int /*<<< orphan*/  mgmtUserActionBeforeBatchUpdate ; 
 int /*<<< orphan*/  mgmtUserActionDecode ; 
 int /*<<< orphan*/  mgmtUserActionDelete ; 
 int /*<<< orphan*/  mgmtUserActionDestroy ; 
 int /*<<< orphan*/  mgmtUserActionEncode ; 
 int /*<<< orphan*/ * mgmtUserActionFp ; 
 int /*<<< orphan*/  mgmtUserActionInsert ; 
 int /*<<< orphan*/  mgmtUserActionReset ; 
 int /*<<< orphan*/  mgmtUserActionUpdate ; 

void mgmtUserActionInit() {
  mgmtUserActionFp[SDB_TYPE_INSERT] = mgmtUserActionInsert;
  mgmtUserActionFp[SDB_TYPE_DELETE] = mgmtUserActionDelete;
  mgmtUserActionFp[SDB_TYPE_UPDATE] = mgmtUserActionUpdate;
  mgmtUserActionFp[SDB_TYPE_ENCODE] = mgmtUserActionEncode;
  mgmtUserActionFp[SDB_TYPE_DECODE] = mgmtUserActionDecode;
  mgmtUserActionFp[SDB_TYPE_BEFORE_BATCH_UPDATE] = mgmtUserActionBeforeBatchUpdate;
  mgmtUserActionFp[SDB_TYPE_BATCH_UPDATE] = mgmtUserActionBatchUpdate;
  mgmtUserActionFp[SDB_TYPE_AFTER_BATCH_UPDATE] = mgmtUserActionAfterBatchUpdate;
  mgmtUserActionFp[SDB_TYPE_RESET] = mgmtUserActionReset;
  mgmtUserActionFp[SDB_TYPE_DESTROY] = mgmtUserActionDestroy;
}