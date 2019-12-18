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
typedef  int /*<<< orphan*/  DiracFrame ;

/* Variables and functions */

__attribute__((used)) static int add_frame(DiracFrame *framelist[], int maxframes, DiracFrame *frame)
{
    int i;
    for (i = 0; i < maxframes; i++)
        if (!framelist[i]) {
            framelist[i] = frame;
            return 0;
        }
    return -1;
}