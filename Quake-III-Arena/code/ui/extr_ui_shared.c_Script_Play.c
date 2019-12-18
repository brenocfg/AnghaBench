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
typedef  int /*<<< orphan*/  itemDef_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* registerSound ) (char const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* startLocalSound ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_LOCAL_SOUND ; 
 TYPE_1__* DC ; 
 scalar_t__ String_Parse (char**,char const**) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (char const*,int /*<<< orphan*/ ) ; 

void Script_Play(itemDef_t *item, char **args) {
	const char *val;
	if (String_Parse(args, &val)) {
		DC->startLocalSound(DC->registerSound(val, qfalse), CHAN_LOCAL_SOUND);
	}
}