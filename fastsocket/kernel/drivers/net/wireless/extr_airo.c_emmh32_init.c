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
struct TYPE_3__ {scalar_t__ position; scalar_t__ accum; } ;
typedef  TYPE_1__ emmh32_context ;

/* Variables and functions */

__attribute__((used)) static void emmh32_init(emmh32_context *context)
{
	/* prepare for new mic calculation */
	context->accum = 0;
	context->position = 0;
}