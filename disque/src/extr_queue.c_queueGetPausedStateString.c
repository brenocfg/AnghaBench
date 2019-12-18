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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_PAUSED_ALL ; 
 int /*<<< orphan*/  QUEUE_FLAG_PAUSED_IN ; 
 int /*<<< orphan*/  QUEUE_FLAG_PAUSED_OUT ; 

char *queueGetPausedStateString(uint32_t qflags) {
    qflags &= QUEUE_FLAG_PAUSED_ALL;
    if (qflags == QUEUE_FLAG_PAUSED_ALL) {
        return "all";
    } else if (qflags == QUEUE_FLAG_PAUSED_IN) {
        return "in";
    } else if (qflags == QUEUE_FLAG_PAUSED_OUT) {
        return "out";
    } else {
        return "none";
    }
}