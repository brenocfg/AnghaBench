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
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_2__ {int adb_type; } ;

/* Variables and functions */
#define  MAC_ADB_CUDA 131 
#define  MAC_ADB_IISI 130 
#define  MAC_ADB_PB1 129 
#define  MAC_ADB_PB2 128 
 int /*<<< orphan*/  cuda_read_pram (int) ; 
 int /*<<< orphan*/  maciisi_read_pram (int) ; 
 TYPE_1__* macintosh_config ; 
 int /*<<< orphan*/  pmu_read_pram (int) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  via_read_pram (int) ; 

void mac_pram_read(int offset, __u8 *buffer, int len)
{
	__u8 (*func)(int);
	int i;

	switch(macintosh_config->adb_type) {
	case MAC_ADB_IISI:
		func = maciisi_read_pram; break;
	case MAC_ADB_PB1:
	case MAC_ADB_PB2:
		func = pmu_read_pram; break;
	case MAC_ADB_CUDA:
		func = cuda_read_pram; break;
	default:
		func = via_read_pram;
	}
	if (!func)
		return;
	for (i = 0 ; i < len ; i++) {
		buffer[i] = (*func)(offset++);
	}
}