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
typedef  int /*<<< orphan*/  mdns_result_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_8__ {TYPE_3__* max_results; TYPE_2__* timeout; TYPE_1__* hostname; int /*<<< orphan*/  end; } ;
struct TYPE_7__ {int* ival; } ;
struct TYPE_6__ {int* ival; } ;
struct TYPE_5__ {char** sval; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDNS_TYPE_ANY ; 
 int arg_parse (int,char**,void**) ; 
 int /*<<< orphan*/  arg_print_errors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdns_print_results (int /*<<< orphan*/ *) ; 
 scalar_t__ mdns_query (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ **) ; 
 TYPE_4__ mdns_query_ip_args ; 
 int /*<<< orphan*/  mdns_query_results_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int cmd_mdns_query_ip(int argc, char** argv)
{
    int nerrors = arg_parse(argc, argv, (void**) &mdns_query_ip_args);
    if (nerrors != 0) {
        arg_print_errors(stderr, mdns_query_ip_args.end, argv[0]);
        return 1;
    }

    const char * hostname = mdns_query_ip_args.hostname->sval[0];
    int timeout = mdns_query_ip_args.timeout->ival[0];
    int max_results = mdns_query_ip_args.max_results->ival[0];

    if (!hostname || !hostname[0]) {
        printf("ERROR: Hostname not supplied\n");
        return 1;
    }

    if (timeout <= 0) {
        timeout = 1000;
    }

    if (max_results < 0 || max_results > 255) {
        max_results = 255;
    }

    printf("Query IP: %s.local, Timeout: %d, Max Results: %d\n", hostname, timeout, max_results);

    mdns_result_t * results = NULL;
    esp_err_t err = mdns_query(hostname, NULL, NULL, MDNS_TYPE_ANY, timeout, max_results, &results);
    if (err) {
        printf("ERROR: Query Failed\n");
        return 1;
    }
    if (!results) {
        printf("No results found!\n");
        return 0;
    }
    mdns_print_results(results);
    mdns_query_results_free(results);

    return 0;
}