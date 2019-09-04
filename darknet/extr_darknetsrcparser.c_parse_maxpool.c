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
typedef  int /*<<< orphan*/  maxpool_layer ;
typedef  int /*<<< orphan*/  list ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  make_maxpool_layer (int,int,int,int,int,int,int) ; 
 int option_find_int (int /*<<< orphan*/ *,char*,int) ; 
 int option_find_int_quiet (int /*<<< orphan*/ *,char*,int) ; 

maxpool_layer parse_maxpool(list *options, size_params params)
{
    int stride = option_find_int(options, "stride",1);
    int size = option_find_int(options, "size",stride);
    int padding = option_find_int_quiet(options, "padding", size-1);

    int batch,h,w,c;
    h = params.h;
    w = params.w;
    c = params.c;
    batch=params.batch;
    if(!(h && w && c)) error("Layer before maxpool layer must output image.");

    maxpool_layer layer = make_maxpool_layer(batch,h,w,c,size,stride,padding);
    return layer;
}