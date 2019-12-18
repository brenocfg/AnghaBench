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
struct TYPE_3__ {int bytestream; int bytestream_start; int outstanding_count; scalar_t__ outstanding_byte; int /*<<< orphan*/  range; } ;
typedef  TYPE_1__ RangeCoder ;

/* Variables and functions */
 int av_log2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int get_rac_count(RangeCoder *c)
{
    int x = c->bytestream - c->bytestream_start + c->outstanding_count;
    if (c->outstanding_byte >= 0)
        x++;
    return 8 * x - av_log2(c->range);
}