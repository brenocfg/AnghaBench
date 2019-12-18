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
struct TYPE_5__ {int /*<<< orphan*/  (* clear_blocks ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/ * block; TYPE_1__ bdsp; } ;
typedef  TYPE_2__ FourXContext ;

/* Variables and functions */
 int decode_i_block (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_i_mb(FourXContext *f)
{
    int ret;
    int i;

    f->bdsp.clear_blocks(f->block[0]);

    for (i = 0; i < 6; i++)
        if ((ret = decode_i_block(f, f->block[i])) < 0)
            return ret;

    return 0;
}