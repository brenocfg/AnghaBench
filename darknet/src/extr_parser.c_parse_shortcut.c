#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int index; int batch; int /*<<< orphan*/  c; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  TYPE_1__ size_params ;
struct TYPE_9__ {TYPE_3__* layers; } ;
typedef  TYPE_2__ network ;
typedef  int /*<<< orphan*/  list ;
struct TYPE_10__ {void* beta; void* alpha; int /*<<< orphan*/  activation; int /*<<< orphan*/  out_c; int /*<<< orphan*/  out_h; int /*<<< orphan*/  out_w; } ;
typedef  TYPE_3__ layer ;
typedef  int /*<<< orphan*/  ACTIVATION ;

/* Variables and functions */
 int atoi (char*) ; 
 int /*<<< orphan*/  get_activation (char*) ; 
 TYPE_3__ make_shortcut_layer (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* option_find (int /*<<< orphan*/ *,char*) ; 
 void* option_find_float_quiet (int /*<<< orphan*/ *,char*,int) ; 
 char* option_find_str (int /*<<< orphan*/ *,char*,char*) ; 

layer parse_shortcut(list *options, size_params params, network *net)
{
    char *l = option_find(options, "from");
    int index = atoi(l);
    if(index < 0) index = params.index + index;

    int batch = params.batch;
    layer from = net->layers[index];

    layer s = make_shortcut_layer(batch, index, params.w, params.h, params.c, from.out_w, from.out_h, from.out_c);

    char *activation_s = option_find_str(options, "activation", "linear");
    ACTIVATION activation = get_activation(activation_s);
    s.activation = activation;
    s.alpha = option_find_float_quiet(options, "alpha", 1);
    s.beta = option_find_float_quiet(options, "beta", 1);
    return s;
}