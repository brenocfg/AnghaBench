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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int enable_read_ahead; scalar_t__ error_flag; scalar_t__ num_sectors_read; int /*<<< orphan*/  FAD; } ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 TYPE_1__ cd_buf ; 
 int /*<<< orphan*/  cd_cs ; 

void SPTICDReadAheadFAD(u32 FAD) {
	EnterCriticalSection(&cd_cs);
	cd_buf.FAD = FAD;
	cd_buf.num_sectors_read = 0;
	cd_buf.error_flag = 0;
	cd_buf.enable_read_ahead = 1;
	LeaveCriticalSection(&cd_cs);
}