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
typedef  int /*<<< orphan*/  note ;
typedef  int /*<<< orphan*/  format ;
struct TYPE_5__ {char** s; int* i; } ;
struct TYPE_6__ {int kind; char* name; char* arg_name; int num_options; char** options; char* help; TYPE_1__ ptr; } ;
typedef  TYPE_2__ FlagDef ;

/* Variables and functions */
#define  FLAG_BOOL 130 
#define  FLAG_ENUM 129 
#define  FLAG_STR 128 
 size_t buf_len (TYPE_2__*) ; 
 TYPE_2__* flag_defs ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

void print_flags_usage(void) {
    printf("Flags:\n");
    for (size_t i = 0; i < buf_len(flag_defs); i++) {
        FlagDef flag = flag_defs[i];
        char note[256] = {0};
        char format[256];
        switch (flag.kind) {
        case FLAG_STR:
            snprintf(format, sizeof(format), "%s <%s>", flag.name, flag.arg_name ? flag.arg_name : "value");
            if (*flag.ptr.s) {
                snprintf(note, sizeof(note), "(default: %s)", *flag.ptr.s);
            }
            break;
        case FLAG_ENUM: {
            char *end = format + sizeof(format);
            char *ptr = format;
            ptr += snprintf(ptr, end - ptr, "%s <", flag.name);
            for (int k = 0; k < flag.num_options; k++) {
                ptr += snprintf(ptr, end - ptr, "%s%s", k == 0 ? "" : "|", flag.options[k]);
                if (k == *flag.ptr.i) {
                    snprintf(note, sizeof(note), " (default: %s)", flag.options[k]);
                }
            }
            snprintf(ptr, end - ptr, ">");
            break;
        }
        case FLAG_BOOL:
        default:
            snprintf(format, sizeof(format), "%s", flag.name);
            break;
        }
        printf(" -%-32s %s%s\n", format, flag.help ? flag.help : "", note);
    }
}