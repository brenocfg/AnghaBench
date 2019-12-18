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
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/  commands; } ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 int /*<<< orphan*/  Lst_IsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_HAS_COMMANDS ; 

__attribute__((used)) static void
ParseHasCommands(void *gnp)
{
    GNode *gn = (GNode *)gnp;
    if (!Lst_IsEmpty(gn->commands)) {
	gn->type |= OP_HAS_COMMANDS;
    }
}