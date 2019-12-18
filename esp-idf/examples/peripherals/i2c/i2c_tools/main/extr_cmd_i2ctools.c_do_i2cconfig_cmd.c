#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* scl; TYPE_3__* sda; TYPE_2__* freq; TYPE_1__* port; int /*<<< orphan*/  end; } ;
struct TYPE_9__ {int /*<<< orphan*/ * ival; } ;
struct TYPE_8__ {int /*<<< orphan*/ * ival; } ;
struct TYPE_7__ {int /*<<< orphan*/ * ival; scalar_t__ count; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ival; scalar_t__ count; } ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int arg_parse (int,char**,void**) ; 
 int /*<<< orphan*/  arg_print_errors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  i2c_frequency ; 
 scalar_t__ i2c_get_port (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_gpio_scl ; 
 int /*<<< orphan*/  i2c_gpio_sda ; 
 int /*<<< orphan*/  i2c_port ; 
 TYPE_5__ i2cconfig_args ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int do_i2cconfig_cmd(int argc, char **argv)
{
    int nerrors = arg_parse(argc, argv, (void **)&i2cconfig_args);
    if (nerrors != 0) {
        arg_print_errors(stderr, i2cconfig_args.end, argv[0]);
        return 0;
    }

    /* Check "--port" option */
    if (i2cconfig_args.port->count) {
        if (i2c_get_port(i2cconfig_args.port->ival[0], &i2c_port) != ESP_OK) {
            return 1;
        }
    }
    /* Check "--freq" option */
    if (i2cconfig_args.freq->count) {
        i2c_frequency = i2cconfig_args.freq->ival[0];
    }
    /* Check "--sda" option */
    i2c_gpio_sda = i2cconfig_args.sda->ival[0];
    /* Check "--scl" option */
    i2c_gpio_scl = i2cconfig_args.scl->ival[0];
    return 0;
}