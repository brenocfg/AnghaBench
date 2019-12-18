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
 void cuda_write_pram (int,int /*<<< orphan*/ ) ; 
 void maciisi_write_pram (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* macintosh_config ; 
 void pmu_write_pram (int,int /*<<< orphan*/ ) ; 
 void stub1 (int,int /*<<< orphan*/ ) ; 
 void via_write_pram (int,int /*<<< orphan*/ ) ; 

void mac_pram_write(int offset, __u8 *buffer, int len)
{
	void (*func)(int, __u8);
	int i;

	switch(macintosh_config->adb_type) {
	case MAC_ADB_IISI:
		func = maciisi_write_pram; break;
	case MAC_ADB_PB1:
	case MAC_ADB_PB2:
		func = pmu_write_pram; break;
	case MAC_ADB_CUDA:
		func = cuda_write_pram; break;
	default:
		func = via_write_pram;
	}
	if (!func)
		return;
	for (i = 0 ; i < len ; i++) {
		(*func)(offset++, buffer[i]);
	}
}