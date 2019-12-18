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
 int /*<<< orphan*/  I_SubmitOutputBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAMPLECOUNT ; 
 int /*<<< orphan*/  mix () ; 
 int /*<<< orphan*/  mixbuffer ; 

void updatesounds(void)
{

    mix();
    I_SubmitOutputBuffer(mixbuffer, SAMPLECOUNT);

}