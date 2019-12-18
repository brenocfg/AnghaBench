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
struct TYPE_5__ {int /*<<< orphan*/  (* execute ) (TYPE_2__*,int /*<<< orphan*/ ,int*,int*,int,int) ;} ;
struct TYPE_4__ {TYPE_2__* avctx; } ;
typedef  TYPE_1__ HEVCContext ;

/* Variables and functions */
 int /*<<< orphan*/  hls_decode_entry ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int*,int*,int,int) ; 

__attribute__((used)) static int hls_slice_data(HEVCContext *s)
{
    int arg[2];
    int ret[2];

    arg[0] = 0;
    arg[1] = 1;

    s->avctx->execute(s->avctx, hls_decode_entry, arg, ret , 1, sizeof(int));
    return ret[0];
}