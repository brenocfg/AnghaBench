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
 int /*<<< orphan*/  mgmtMeterActionAfterBatchUpdate ; 
 int /*<<< orphan*/  mgmtMeterActionBatchUpdate ; 
 int /*<<< orphan*/  mgmtMeterActionBeforeBatchUpdate ; 
 int /*<<< orphan*/  mgmtMeterActionDecode ; 
 int /*<<< orphan*/  mgmtMeterActionDelete ; 
 int /*<<< orphan*/  mgmtMeterActionDestroy ; 
 int /*<<< orphan*/  mgmtMeterActionEncode ; 
 int /*<<< orphan*/ * mgmtMeterActionFp ; 
 int /*<<< orphan*/  mgmtMeterActionInsert ; 
 int /*<<< orphan*/  mgmtMeterActionReset ; 
 int /*<<< orphan*/  mgmtMeterActionUpdate ; 

void mgmtMeterActionInit() {
  mgmtMeterActionFp[SDB_TYPE_INSERT] = mgmtMeterActionInsert;
  mgmtMeterActionFp[SDB_TYPE_DELETE] = mgmtMeterActionDelete;
  mgmtMeterActionFp[SDB_TYPE_UPDATE] = mgmtMeterActionUpdate;
  mgmtMeterActionFp[SDB_TYPE_ENCODE] = mgmtMeterActionEncode;
  mgmtMeterActionFp[SDB_TYPE_DECODE] = mgmtMeterActionDecode;
  mgmtMeterActionFp[SDB_TYPE_BEFORE_BATCH_UPDATE] = mgmtMeterActionBeforeBatchUpdate;
  mgmtMeterActionFp[SDB_TYPE_BATCH_UPDATE] = mgmtMeterActionBatchUpdate;
  mgmtMeterActionFp[SDB_TYPE_AFTER_BATCH_UPDATE] = mgmtMeterActionAfterBatchUpdate;
  mgmtMeterActionFp[SDB_TYPE_RESET] = mgmtMeterActionReset;
  mgmtMeterActionFp[SDB_TYPE_DESTROY] = mgmtMeterActionDestroy;
}