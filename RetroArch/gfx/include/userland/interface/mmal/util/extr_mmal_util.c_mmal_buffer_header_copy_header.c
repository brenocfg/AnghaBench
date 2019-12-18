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
struct TYPE_4__ {int /*<<< orphan*/ * type; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; int /*<<< orphan*/  flags; int /*<<< orphan*/  length; int /*<<< orphan*/  offset; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_1__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */

void mmal_buffer_header_copy_header(MMAL_BUFFER_HEADER_T *dest, const MMAL_BUFFER_HEADER_T *src)
{
   dest->cmd    = src->cmd;
   dest->offset = src->offset;
   dest->length = src->length;
   dest->flags  = src->flags;
   dest->pts    = src->pts;
   dest->dts    = src->dts;
   *dest->type = *src->type;
}