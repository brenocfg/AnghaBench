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
struct TYPE_4__ {TYPE_1__* ssid; int /*<<< orphan*/  end; } ;
struct TYPE_3__ {int count; int /*<<< orphan*/ ** sval; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int arg_parse (int,char**,void**) ; 
 int /*<<< orphan*/  arg_print_errors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ scan_args ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  wifi_cmd_sta_scan (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wifi_cmd_scan(int argc, char** argv)
{
    int nerrors = arg_parse(argc, argv, (void**) &scan_args);

    if (nerrors != 0) {
        arg_print_errors(stderr, scan_args.end, argv[0]);
        return 1;
    }

    ESP_LOGI(TAG, "sta start to scan");
    if ( scan_args.ssid->count == 1 ) {
        wifi_cmd_sta_scan(scan_args.ssid->sval[0]);
    } else {
        wifi_cmd_sta_scan(NULL);
    }
    return 0;
}