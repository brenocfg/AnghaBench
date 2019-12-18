#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* sval; TYPE_1__* file; } ;
typedef  TYPE_2__ Token ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int enable_warning ; 
 int /*<<< orphan*/  errort (TYPE_2__*,char*,char*) ; 
 char* fullpath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_put (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  once ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void parse_pragma_operand(Token *tok) {
    char *s = tok->sval;
    if (!strcmp(s, "once")) {
        char *path = fullpath(tok->file->name);
        map_put(once, path, (void *)1);
    } else if (!strcmp(s, "enable_warning")) {
        enable_warning = true;
    } else if (!strcmp(s, "disable_warning")) {
        enable_warning = false;
    } else {
        errort(tok, "unknown #pragma: %s", s);
    }
}