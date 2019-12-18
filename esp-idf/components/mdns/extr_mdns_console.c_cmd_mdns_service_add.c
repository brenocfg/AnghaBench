#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mdns_txt_item_t ;
struct TYPE_12__ {TYPE_5__* txt; TYPE_4__* port; TYPE_3__* proto; TYPE_2__* service; TYPE_1__* instance; int /*<<< orphan*/  end; } ;
struct TYPE_11__ {scalar_t__ count; int /*<<< orphan*/  sval; } ;
struct TYPE_10__ {int /*<<< orphan*/ * ival; } ;
struct TYPE_9__ {int /*<<< orphan*/ * sval; } ;
struct TYPE_8__ {int /*<<< orphan*/ * sval; } ;
struct TYPE_7__ {char** sval; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _convert_items (int /*<<< orphan*/ ,scalar_t__) ; 
 int arg_parse (int,char**,void**) ; 
 int /*<<< orphan*/  arg_print_errors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_6__ mdns_add_args ; 
 int /*<<< orphan*/  mdns_service_add (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int cmd_mdns_service_add(int argc, char** argv)
{
    int nerrors = arg_parse(argc, argv, (void**) &mdns_add_args);
    if (nerrors != 0) {
        arg_print_errors(stderr, mdns_add_args.end, argv[0]);
        return 1;
    }

    if (!mdns_add_args.service->sval[0] || !mdns_add_args.proto->sval[0] || !mdns_add_args.port->ival[0]) {
        printf("ERROR: Bad arguments!\n");
        return 1;
    }
    const char * instance = NULL;
    if (mdns_add_args.instance->sval[0] && mdns_add_args.instance->sval[0][0]) {
        instance = mdns_add_args.instance->sval[0];
        printf("MDNS: Service Instance: %s\n", instance);
    }
    mdns_txt_item_t * items = NULL;
    if (mdns_add_args.txt->count) {
        items = _convert_items(mdns_add_args.txt->sval, mdns_add_args.txt->count);
        if (!items) {
            printf("ERROR: No Memory!\n");
            return 1;

        }
    }

    ESP_ERROR_CHECK( mdns_service_add(instance, mdns_add_args.service->sval[0], mdns_add_args.proto->sval[0], mdns_add_args.port->ival[0], items, mdns_add_args.txt->count) );
    free(items);
    return 0;
}