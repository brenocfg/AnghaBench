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
 int /*<<< orphan*/  CPU_ClrN ; 
 int CPU_regY ; 
 int /*<<< orphan*/  Devices_GetIOCB () ; 
 int /*<<< orphan*/  Log_print (char*) ; 
 int /*<<< orphan*/  Util_fclose (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ devbug ; 
 int /*<<< orphan*/ ** h_fp ; 
 size_t h_iocb ; 
 int /*<<< orphan*/ * h_tmpbuf ; 

__attribute__((used)) static void Devices_H_Close(void)
{
	if (devbug)
		Log_print("HHCLOS");
	if (!Devices_GetIOCB())
		return;
	if (h_fp[h_iocb] != NULL) {
		Util_fclose(h_fp[h_iocb], h_tmpbuf[h_iocb]);
		h_fp[h_iocb] = NULL;
	}
	CPU_regY = 1;
	CPU_ClrN;
}