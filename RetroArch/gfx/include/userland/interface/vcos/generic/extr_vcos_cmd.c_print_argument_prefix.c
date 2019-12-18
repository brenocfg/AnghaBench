#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * argv_orig; int /*<<< orphan*/ * argv; } ;
typedef  TYPE_1__ VCOS_CMD_PARAM_T ;

/* Variables and functions */
 int /*<<< orphan*/  vcos_cmd_printf (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_argument_prefix( VCOS_CMD_PARAM_T *param )
{
    int arg_idx;

    for ( arg_idx = 0; &param->argv_orig[arg_idx] != param->argv; arg_idx++ )
    {
        vcos_cmd_printf( param, "%s ", param->argv_orig[arg_idx] );
    }
}