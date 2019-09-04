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
struct TYPE_3__ {scalar_t__ mode; size_t partitioning; int /*<<< orphan*/  const* bmv; } ;
typedef  TYPE_1__ VP8Macroblock ;
typedef  int /*<<< orphan*/  VP56mv ;

/* Variables and functions */
 scalar_t__ VP8_MVMODE_SPLIT ; 
 size_t** vp8_mbsplits ; 

__attribute__((used)) static const VP56mv *get_bmv_ptr(const VP8Macroblock *mb, int subblock)
{
    return &mb->bmv[mb->mode == VP8_MVMODE_SPLIT ? vp8_mbsplits[mb->partitioning][subblock] : 0];
}