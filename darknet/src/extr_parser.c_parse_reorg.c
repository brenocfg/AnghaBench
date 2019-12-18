#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int h; int w; int c; int batch; } ;
typedef  TYPE_1__ size_params ;
typedef  int /*<<< orphan*/  list ;
typedef  int /*<<< orphan*/  layer ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  make_reorg_layer (int,int,int,int,int,int,int,int) ; 
 int option_find_int (int /*<<< orphan*/ *,char*,int) ; 
 int option_find_int_quiet (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

layer parse_reorg(list *options, size_params params)
{
    int stride = option_find_int(options, "stride",1);
    int reverse = option_find_int_quiet(options, "reverse",0);
    int flatten = option_find_int_quiet(options, "flatten",0);
    int extra = option_find_int_quiet(options, "extra",0);

    int batch,h,w,c;
    h = params.h;
    w = params.w;
    c = params.c;
    batch=params.batch;
    if(!(h && w && c)) error("Layer before reorg layer must output image.");

    layer layer = make_reorg_layer(batch,w,h,c,stride,reverse, flatten, extra);
    return layer;
}