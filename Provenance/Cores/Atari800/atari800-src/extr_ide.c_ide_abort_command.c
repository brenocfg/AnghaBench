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
struct ide_device {int status; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABRT_ERR ; 
 int ERR_STAT ; 
 int READY_STAT ; 

__attribute__((used)) static inline void ide_abort_command(struct ide_device *s) {
    s->status = READY_STAT | ERR_STAT;
    s->error  = ABRT_ERR;
}