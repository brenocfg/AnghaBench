#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* sync ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ DB ;

/* Variables and functions */
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
state_sync(DB *db)
{
	return (*db->sync)(db, 0);
}