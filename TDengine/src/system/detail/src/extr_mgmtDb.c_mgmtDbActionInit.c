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
 int /*<<< orphan*/  mgmtDbActionAfterBatchUpdate ; 
 int /*<<< orphan*/  mgmtDbActionBatchUpdate ; 
 int /*<<< orphan*/  mgmtDbActionBeforeBatchUpdate ; 
 int /*<<< orphan*/  mgmtDbActionDecode ; 
 int /*<<< orphan*/  mgmtDbActionDelete ; 
 int /*<<< orphan*/  mgmtDbActionDestroy ; 
 int /*<<< orphan*/  mgmtDbActionEncode ; 
 int /*<<< orphan*/ * mgmtDbActionFp ; 
 int /*<<< orphan*/  mgmtDbActionInsert ; 
 int /*<<< orphan*/  mgmtDbActionReset ; 
 int /*<<< orphan*/  mgmtDbActionUpdate ; 

void mgmtDbActionInit() {
  mgmtDbActionFp[SDB_TYPE_INSERT] = mgmtDbActionInsert;
  mgmtDbActionFp[SDB_TYPE_DELETE] = mgmtDbActionDelete;
  mgmtDbActionFp[SDB_TYPE_UPDATE] = mgmtDbActionUpdate;
  mgmtDbActionFp[SDB_TYPE_ENCODE] = mgmtDbActionEncode;
  mgmtDbActionFp[SDB_TYPE_DECODE] = mgmtDbActionDecode;
  mgmtDbActionFp[SDB_TYPE_BEFORE_BATCH_UPDATE] = mgmtDbActionBeforeBatchUpdate;
  mgmtDbActionFp[SDB_TYPE_BATCH_UPDATE] = mgmtDbActionBatchUpdate;
  mgmtDbActionFp[SDB_TYPE_AFTER_BATCH_UPDATE] = mgmtDbActionAfterBatchUpdate;
  mgmtDbActionFp[SDB_TYPE_RESET] = mgmtDbActionReset;
  mgmtDbActionFp[SDB_TYPE_DESTROY] = mgmtDbActionDestroy;
}