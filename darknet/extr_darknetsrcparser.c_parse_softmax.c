#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  c; int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  inputs; int /*<<< orphan*/  batch; } ;
typedef  TYPE_1__ size_params ;
typedef  int /*<<< orphan*/  list ;
struct TYPE_7__ {void* noloss; void* spatial; int /*<<< orphan*/  c; int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  softmax_tree; void* temperature; } ;
typedef  TYPE_2__ layer ;

/* Variables and functions */
 TYPE_2__ make_softmax_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* option_find_float_quiet (int /*<<< orphan*/ *,char*,int) ; 
 void* option_find_int_quiet (int /*<<< orphan*/ *,char*,int) ; 
 char* option_find_str (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_tree (char*) ; 

layer parse_softmax(list *options, size_params params)
{
    int groups = option_find_int_quiet(options, "groups",1);
    layer l = make_softmax_layer(params.batch, params.inputs, groups);
    l.temperature = option_find_float_quiet(options, "temperature", 1);
    char *tree_file = option_find_str(options, "tree", 0);
    if (tree_file) l.softmax_tree = read_tree(tree_file);
    l.w = params.w;
    l.h = params.h;
    l.c = params.c;
    l.spatial = option_find_float_quiet(options, "spatial", 0);
    l.noloss =  option_find_int_quiet(options, "noloss", 0);
    return l;
}