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
 int JOB_STATE_ACKED ; 

char *jobStateToString(int state) {
    char *states[] = {"wait-repl","active","queued","acked"};
    if (state < 0 || state > JOB_STATE_ACKED) return "unknown";
    return states[state];
}