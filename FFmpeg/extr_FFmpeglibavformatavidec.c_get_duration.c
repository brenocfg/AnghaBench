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
struct TYPE_3__ {int dshow_block_align; scalar_t__ sample_size; } ;
typedef  TYPE_1__ AVIStream ;

/* Variables and functions */

__attribute__((used)) static inline int get_duration(AVIStream *ast, int len)
{
    if (ast->sample_size)
        return len;
    else if (ast->dshow_block_align)
        return (len + ast->dshow_block_align - 1) / ast->dshow_block_align;
    else
        return 1;
}