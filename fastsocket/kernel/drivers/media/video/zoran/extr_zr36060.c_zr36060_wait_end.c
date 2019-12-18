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
struct zr36060 {int /*<<< orphan*/  status; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ZR060_CFSR_Busy ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int zr36060_read_status (struct zr36060*) ; 

__attribute__((used)) static void
zr36060_wait_end (struct zr36060 *ptr)
{
	int i = 0;

	while (zr36060_read_status(ptr) & ZR060_CFSR_Busy) {
		udelay(1);
		if (i++ > 200000) {	// 200ms, there is for sure something wrong!!!
			dprintk(1,
				"%s: timeout at wait_end (last status: 0x%02x)\n",
				ptr->name, ptr->status);
			break;
		}
	}
}