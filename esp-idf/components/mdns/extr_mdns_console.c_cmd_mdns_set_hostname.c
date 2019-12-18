#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* hostname; int /*<<< orphan*/  end; } ;
struct TYPE_3__ {int /*<<< orphan*/ ** sval; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int arg_parse (int,char**,void**) ; 
 int /*<<< orphan*/  arg_print_errors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdns_hostname_set (int /*<<< orphan*/ *) ; 
 TYPE_2__ mdns_set_hostname_args ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int cmd_mdns_set_hostname(int argc, char** argv)
{
    int nerrors = arg_parse(argc, argv, (void**) &mdns_set_hostname_args);
    if (nerrors != 0) {
        arg_print_errors(stderr, mdns_set_hostname_args.end, argv[0]);
        return 1;
    }

    if (mdns_set_hostname_args.hostname->sval[0] == NULL) {
        printf("ERROR: Bad arguments!\n");
        return 1;
    }

    ESP_ERROR_CHECK( mdns_hostname_set(mdns_set_hostname_args.hostname->sval[0]) );
    return 0;
}