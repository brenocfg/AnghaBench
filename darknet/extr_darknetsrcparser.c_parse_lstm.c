#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* net; int /*<<< orphan*/  time_steps; int /*<<< orphan*/  inputs; int /*<<< orphan*/  batch; } ;
typedef  TYPE_2__ size_params ;
typedef  int /*<<< orphan*/  list ;
typedef  int /*<<< orphan*/  layer ;
struct TYPE_4__ {int /*<<< orphan*/  adam; } ;

/* Variables and functions */
 int /*<<< orphan*/  make_lstm_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int option_find_int (int /*<<< orphan*/ *,char*,int) ; 
 int option_find_int_quiet (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

layer parse_lstm(list *options, size_params params)
{
    int output = option_find_int(options, "output", 1);
    int batch_normalize = option_find_int_quiet(options, "batch_normalize", 0);

    layer l = make_lstm_layer(params.batch, params.inputs, output, params.time_steps, batch_normalize, params.net->adam);

    return l;
}