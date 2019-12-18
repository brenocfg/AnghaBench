#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  data; int /*<<< orphan*/  alloc_size; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; int /*<<< orphan*/  flags; int /*<<< orphan*/  length; int /*<<< orphan*/  offset; int /*<<< orphan*/  cmd; } ;
struct TYPE_7__ {int /*<<< orphan*/  buffer_header_type_specific; TYPE_1__ buffer_header; } ;
typedef  TYPE_2__ mmal_worker_buffer_from_host ;
struct TYPE_8__ {int /*<<< orphan*/ * type; int /*<<< orphan*/  data; int /*<<< orphan*/  alloc_size; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; int /*<<< orphan*/  flags; int /*<<< orphan*/  length; int /*<<< orphan*/  offset; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_3__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */

__attribute__((used)) static inline void mmal_vc_buffer_header_to_msg(mmal_worker_buffer_from_host *msg,
                                                MMAL_BUFFER_HEADER_T *header)
{
   msg->buffer_header.cmd           = header->cmd;
   msg->buffer_header.offset        = header->offset;
   msg->buffer_header.length        = header->length;
   msg->buffer_header.flags         = header->flags;
   msg->buffer_header.pts           = header->pts;
   msg->buffer_header.dts           = header->dts;
   msg->buffer_header.alloc_size    = header->alloc_size;
   msg->buffer_header.data          = header->data;
   msg->buffer_header_type_specific = *header->type;
}