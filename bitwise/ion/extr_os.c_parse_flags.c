#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* b; char const** s; int* i; } ;
struct TYPE_5__ {int kind; int num_options; TYPE_1__ ptr; int /*<<< orphan*/ * options; } ;
typedef  TYPE_2__ FlagDef ;

/* Variables and functions */
#define  FLAG_BOOL 130 
#define  FLAG_ENUM 129 
#define  FLAG_STR 128 
 TYPE_2__* get_flag_def (char const*) ; 
 char const* path_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

const char *parse_flags(int *argc_ptr, const char ***argv_ptr) {
    int argc = *argc_ptr;
    const char **argv = *argv_ptr;
    int i;
    for (i = 1; i < argc; i++) {
        const char *arg = argv[i];
        const char *name = arg;
        if (*name== '-') {
            name++;
            if (*name== '-') {
                name++;
            }
            FlagDef *flag = get_flag_def(name);
            if (!flag) {
                printf("Unknown flag %s\n", arg);
                continue;
            }
            switch (flag->kind) {
            case FLAG_BOOL:
                *flag->ptr.b = true;
                break;
            case FLAG_STR:
                if (i + 1 < argc) {
                    i++;
                    *flag->ptr.s = argv[i];
                } else {
                    printf("No value argument after -%s\n", arg);
                }
                break;
            case FLAG_ENUM: {
                const char *option;
                if (i + 1 < argc) {
                    i++;
                    option = argv[i];
                } else {
                    printf("No value after %s\n", arg);
                    break;
                }
                bool found = false;
                for (int k = 0; k < flag->num_options; k++) {
                    if (strcmp(flag->options[k], option) == 0) {
                        *flag->ptr.i = k;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    printf("Invalid value '%s' for %s\n", option, arg);
                }
                break;
            }
            default:
                printf("Unhandled flag kind\n");
                break;
            }
        } else {
            break;
        }
    }
    *argc_ptr = argc - i;
    *argv_ptr = argv + i;
    return path_file(strdup(argv[0]));
}