#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* instance; TYPE_1__* hostname; int /*<<< orphan*/  end; } ;
struct TYPE_5__ {char** sval; } ;
struct TYPE_4__ {char** sval; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int arg_parse (int,char**,void**) ; 
 int /*<<< orphan*/  arg_print_errors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdns_hostname_set (char*) ; 
 int /*<<< orphan*/  mdns_init () ; 
 TYPE_3__ mdns_init_args ; 
 int /*<<< orphan*/  mdns_instance_name_set (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int cmd_mdns_init(int argc, char** argv)
{
    int nerrors = arg_parse(argc, argv, (void**) &mdns_init_args);
    if (nerrors != 0) {
        arg_print_errors(stderr, mdns_init_args.end, argv[0]);
        return 1;
    }

    ESP_ERROR_CHECK( mdns_init() );

    if (mdns_init_args.hostname->sval[0]) {
        ESP_ERROR_CHECK( mdns_hostname_set(mdns_init_args.hostname->sval[0]) );
        printf("MDNS: Hostname: %s\n", mdns_init_args.hostname->sval[0]);
    }

    if (mdns_init_args.instance->sval[0]) {
        ESP_ERROR_CHECK( mdns_instance_name_set(mdns_init_args.instance->sval[0]) );
        printf("MDNS: Instance: %s\n", mdns_init_args.instance->sval[0]);
    }

    return 0;
}