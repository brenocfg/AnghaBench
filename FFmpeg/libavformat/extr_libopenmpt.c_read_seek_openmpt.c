#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  module; } ;
typedef  TYPE_1__ OpenMPTContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 double AV_TIME_BASE ; 
 int /*<<< orphan*/  openmpt_module_set_position_seconds (int /*<<< orphan*/ ,double) ; 

__attribute__((used)) static int read_seek_openmpt(AVFormatContext *s, int stream_idx, int64_t ts, int flags)
{
    OpenMPTContext *openmpt = s->priv_data;
    openmpt_module_set_position_seconds(openmpt->module, (double)ts/AV_TIME_BASE);
    return 0;
}