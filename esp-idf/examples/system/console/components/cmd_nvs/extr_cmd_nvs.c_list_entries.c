#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* type; TYPE_2__* namespace; TYPE_1__* partition; int /*<<< orphan*/  end; } ;
struct TYPE_7__ {char** sval; } ;
struct TYPE_6__ {char** sval; } ;
struct TYPE_5__ {char** sval; } ;

/* Variables and functions */
 int arg_parse (int,char**,void**) ; 
 int /*<<< orphan*/  arg_print_errors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int list (char const*,char const*,char const*) ; 
 TYPE_4__ list_args ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int list_entries(int argc, char **argv)
{
    list_args.partition->sval[0] = "";
    list_args.namespace->sval[0] = "";
    list_args.type->sval[0] = "";

    int nerrors = arg_parse(argc, argv, (void **) &list_args);
    if (nerrors != 0) {
        arg_print_errors(stderr, list_args.end, argv[0]);
        return 1;
    }

    const char *part = list_args.partition->sval[0];
    const char *name = list_args.namespace->sval[0];
    const char *type = list_args.type->sval[0];

    return list(part, name, type);
}