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
typedef  int /*<<< orphan*/  job ;
struct TYPE_2__ {scalar_t__ aof_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AOFDelJob (int /*<<< orphan*/ *) ; 
 scalar_t__ AOF_OFF ; 
 TYPE_1__ server ; 

void AOFAckJob(job *job) {
    if (server.aof_state == AOF_OFF) return;
    AOFDelJob(job);
}