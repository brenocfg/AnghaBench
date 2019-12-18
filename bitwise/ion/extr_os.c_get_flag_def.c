#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ FlagDef ;

/* Variables and functions */
 size_t buf_len (TYPE_1__*) ; 
 TYPE_1__* flag_defs ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

FlagDef *get_flag_def(const char *name) {
    for (size_t i = 0; i < buf_len(flag_defs); i++) {
        if (strcmp(flag_defs[i].name, name) == 0) {
            return &flag_defs[i];
        }
    }
    return NULL;
}