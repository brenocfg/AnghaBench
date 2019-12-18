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
struct TYPE_5__ {scalar_t__ type; scalar_t__ name; } ;
typedef  TYPE_1__ AVOption ;

/* Variables and functions */
 scalar_t__ AV_OPT_TYPE_CONST ; 
 int /*<<< orphan*/  print_option (TYPE_1__ const*,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void show_opts(const AVOption *opts, int per_stream)
{
    const AVOption *o;

    printf("@table @option\n");
    for (o = opts; o->name; o++) {
        if (o->type != AV_OPT_TYPE_CONST)
            print_option(opts, o, per_stream);
    }
    printf("@end table\n");
}