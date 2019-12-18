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
struct TYPE_5__ {TYPE_1__* avctx; } ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_2__ MotionEstContext ;

/* Variables and functions */
 int AV_CODEC_FLAG_QPEL ; 
 int FLAG_CHROMA ; 
 int FLAG_DIRECT ; 
 int FLAG_QPEL ; 

__attribute__((used)) static int get_flags(MotionEstContext *c, int direct, int chroma){
    return   ((c->avctx->flags&AV_CODEC_FLAG_QPEL) ? FLAG_QPEL : 0)
           + (direct ? FLAG_DIRECT : 0)
           + (chroma ? FLAG_CHROMA : 0);
}