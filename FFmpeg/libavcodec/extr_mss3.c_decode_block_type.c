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
struct TYPE_3__ {size_t last_type; int /*<<< orphan*/ * bt_model; } ;
typedef  int /*<<< orphan*/  RangeCoder ;
typedef  TYPE_1__ BlockTypeContext ;

/* Variables and functions */
 size_t rac_get_model_sym (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_block_type(RangeCoder *c, BlockTypeContext *bt)
{
    bt->last_type = rac_get_model_sym(c, &bt->bt_model[bt->last_type]);

    return bt->last_type;
}