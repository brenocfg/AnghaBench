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
struct TYPE_4__ {int /*<<< orphan*/  done_out_buffers; int /*<<< orphan*/  num_done_out_buffers; int /*<<< orphan*/  output_cond; int /*<<< orphan*/  output_mutex; } ;
typedef  TYPE_1__* OMX_PTR ;
typedef  int /*<<< orphan*/  OMX_HANDLETYPE ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  int /*<<< orphan*/  OMX_BUFFERHEADERTYPE ;
typedef  TYPE_1__ OMXCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  OMX_ErrorNone ; 
 int /*<<< orphan*/  append_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static OMX_ERRORTYPE fill_buffer_done(OMX_HANDLETYPE component, OMX_PTR app_data,
                                      OMX_BUFFERHEADERTYPE *buffer)
{
    OMXCodecContext *s = app_data;
    append_buffer(&s->output_mutex, &s->output_cond,
                  &s->num_done_out_buffers, s->done_out_buffers, buffer);
    return OMX_ErrorNone;
}