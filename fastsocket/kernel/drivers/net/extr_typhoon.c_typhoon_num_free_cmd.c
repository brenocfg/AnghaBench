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
struct TYPE_3__ {int lastWrite; } ;
struct typhoon {TYPE_2__* indexes; TYPE_1__ cmdRing; } ;
struct TYPE_4__ {int /*<<< orphan*/  cmdCleared; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_ENTRIES ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int typhoon_num_free (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
typhoon_num_free_cmd(struct typhoon *tp)
{
	int lastWrite = tp->cmdRing.lastWrite;
	int cmdCleared = le32_to_cpu(tp->indexes->cmdCleared);

	return typhoon_num_free(lastWrite, cmdCleared, COMMAND_ENTRIES);
}