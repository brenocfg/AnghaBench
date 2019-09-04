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
struct TYPE_5__ {scalar_t__ type; } ;
typedef  TYPE_1__ AVOption ;
typedef  int /*<<< orphan*/  AVClass ;

/* Variables and functions */
 scalar_t__ FF_OPT_TYPE_CONST ; 
 TYPE_1__* av_next_option (int /*<<< orphan*/  const**,TYPE_1__ const*) ; 
 int /*<<< orphan*/  print_option (int /*<<< orphan*/  const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void show_opts(const AVClass *class)
{
    const AVOption *o = NULL;

    printf("@table @option\n");
    while ((o = av_next_option(&class, o)))
        if (o->type != FF_OPT_TYPE_CONST)
            print_option(class, o);
    printf("@end table\n");
}