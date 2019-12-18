#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ipc_importance_inherit_t ;
struct TYPE_3__ {int /*<<< orphan*/  iii_elem; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipc_importance_release_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
ipc_importance_inherit_release_locked(ipc_importance_inherit_t inherit)
{
	ipc_importance_release_locked(&inherit->iii_elem);
}