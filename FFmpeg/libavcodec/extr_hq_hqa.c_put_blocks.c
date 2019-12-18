#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_8__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* idct_put ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {TYPE_1__ hqhqadsp; } ;
typedef  TYPE_2__ HQContext ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void put_blocks(HQContext *c, AVFrame *pic,
                              int plane, int x, int y, int ilace,
                              int16_t *block0, int16_t *block1)
{
    uint8_t *p = pic->data[plane] + x;

    c->hqhqadsp.idct_put(p + y * pic->linesize[plane],
                         pic->linesize[plane] << ilace, block0);
    c->hqhqadsp.idct_put(p + (y + (ilace ? 1 : 8)) * pic->linesize[plane],
                         pic->linesize[plane] << ilace, block1);
}