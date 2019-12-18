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
struct serverCommand {int dummy; } ;
typedef  int /*<<< orphan*/  sds ;
struct TYPE_2__ {int /*<<< orphan*/  orig_commands; int /*<<< orphan*/  commands; } ;

/* Variables and functions */
 struct serverCommand* dictFetchValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ server ; 

struct serverCommand *lookupCommandOrOriginal(sds name) {
    struct serverCommand *cmd = dictFetchValue(server.commands, name);

    if (!cmd) cmd = dictFetchValue(server.orig_commands,name);
    return cmd;
}