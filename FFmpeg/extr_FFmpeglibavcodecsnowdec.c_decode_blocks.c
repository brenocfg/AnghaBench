#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ bytestream; scalar_t__ bytestream_end; } ;
struct TYPE_6__ {int b_width; int b_height; TYPE_1__ c; } ;
typedef  TYPE_2__ SnowContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int decode_q_branch (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int decode_blocks(SnowContext *s){
    int x, y;
    int w= s->b_width;
    int h= s->b_height;
    int res;

    for(y=0; y<h; y++){
        for(x=0; x<w; x++){
            if (s->c.bytestream >= s->c.bytestream_end)
                return AVERROR_INVALIDDATA;
            if ((res = decode_q_branch(s, 0, x, y)) < 0)
                return res;
        }
    }
    return 0;
}