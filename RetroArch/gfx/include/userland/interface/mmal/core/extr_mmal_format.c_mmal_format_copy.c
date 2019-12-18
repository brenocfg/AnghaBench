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
struct TYPE_4__ {scalar_t__ extradata_size; scalar_t__ extradata; int /*<<< orphan*/ * es; } ;
typedef  TYPE_1__ MMAL_ES_FORMAT_T ;

/* Variables and functions */

void mmal_format_copy(MMAL_ES_FORMAT_T *fmt_dst, MMAL_ES_FORMAT_T *fmt_src)
{
   void *backup = fmt_dst->es;
   *fmt_dst->es = *fmt_src->es;
   *fmt_dst = *fmt_src;
   fmt_dst->es = backup;
   fmt_dst->extradata = 0;
   fmt_dst->extradata_size = 0;
}