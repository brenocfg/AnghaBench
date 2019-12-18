#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ubifs_info {TYPE_2__* jheads; } ;
struct TYPE_3__ {int /*<<< orphan*/  io_mutex; } ;
struct TYPE_4__ {TYPE_1__ wbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void release_head(struct ubifs_info *c, int jhead)
{
	mutex_unlock(&c->jheads[jhead].wbuf.io_mutex);
}