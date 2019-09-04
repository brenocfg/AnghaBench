#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int filter_mode; } ;
typedef  TYPE_1__ DCACoreDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  erase_dsp_history (TYPE_1__*) ; 

__attribute__((used)) static void set_filter_mode(DCACoreDecoder *s, int mode)
{
    if (s->filter_mode != mode) {
        erase_dsp_history(s);
        s->filter_mode = mode;
    }
}