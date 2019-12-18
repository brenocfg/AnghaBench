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
struct TYPE_3__ {scalar_t__ output_history_lfe_float; scalar_t__ output_history_lfe_fixed; int /*<<< orphan*/  dcadsp_data; } ;
typedef  TYPE_1__ DCACoreDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void erase_dsp_history(DCACoreDecoder *s)
{
    memset(s->dcadsp_data, 0, sizeof(s->dcadsp_data));
    s->output_history_lfe_fixed = 0;
    s->output_history_lfe_float = 0;
}