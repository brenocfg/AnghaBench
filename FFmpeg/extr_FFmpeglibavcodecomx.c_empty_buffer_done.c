#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * pAppPrivate; scalar_t__ pOutputPortPrivate; } ;
struct TYPE_7__ {int /*<<< orphan*/  free_in_buffers; int /*<<< orphan*/  num_free_in_buffers; int /*<<< orphan*/  input_cond; int /*<<< orphan*/  input_mutex; scalar_t__ input_zerocopy; } ;
typedef  TYPE_1__* OMX_PTR ;
typedef  int /*<<< orphan*/  OMX_HANDLETYPE ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  TYPE_2__ OMX_BUFFERHEADERTYPE ;
typedef  TYPE_1__ OMXCodecContext ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  OMX_ErrorNone ; 
 int /*<<< orphan*/  append_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static OMX_ERRORTYPE empty_buffer_done(OMX_HANDLETYPE component, OMX_PTR app_data,
                                       OMX_BUFFERHEADERTYPE *buffer)
{
    OMXCodecContext *s = app_data;
    if (s->input_zerocopy) {
        if (buffer->pAppPrivate) {
            if (buffer->pOutputPortPrivate)
                av_free(buffer->pAppPrivate);
            else
                av_frame_free((AVFrame**)&buffer->pAppPrivate);
            buffer->pAppPrivate = NULL;
        }
    }
    append_buffer(&s->input_mutex, &s->input_cond,
                  &s->num_free_in_buffers, s->free_in_buffers, buffer);
    return OMX_ErrorNone;
}