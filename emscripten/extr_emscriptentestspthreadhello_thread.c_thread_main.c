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
 int /*<<< orphan*/  EM_ASM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out (char) ; 

void *thread_main(void *arg)
{
	EM_ASM(out('hello from thread!'));
#ifdef REPORT_RESULT
	REPORT_RESULT(1);
#endif
	return 0;
}