#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_8__ {TYPE_1__* ps_ResultTupleSlot; } ;
struct TYPE_9__ {TYPE_2__ ps; } ;
struct TYPE_10__ {TYPE_3__ ss; } ;
struct TYPE_11__ {TYPE_4__ customScanState; } ;
struct TYPE_7__ {int /*<<< orphan*/  tts_tupleDescriptor; } ;
typedef  TYPE_5__ CitusScanState ;

/* Variables and functions */

TupleDesc
ScanStateGetTupleDescriptor(CitusScanState *scanState)
{
	return scanState->customScanState.ss.ps.ps_ResultTupleSlot->tts_tupleDescriptor;
}