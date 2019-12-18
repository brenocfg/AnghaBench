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
struct moveparams {int dummy; } ;

/* Variables and functions */
 scalar_t__ CONFIG_KERNEL_TEXT_ADDRESS ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  debugflag ; 
 int /*<<< orphan*/  gunzip () ; 
 int /*<<< orphan*/  kputs (char*) ; 
 int /*<<< orphan*/  makecrc () ; 
 char* output_data ; 

int decompress_kernel(struct moveparams *mv)
{
#ifdef DEBUGFLAG
	while (!debugflag)
		barrier();
#endif

	output_data = (char *) CONFIG_KERNEL_TEXT_ADDRESS;

	makecrc();
	kputs("Uncompressing Linux... ");
	gunzip();
	kputs("Ok, booting the kernel.\n");
	return 0;
}