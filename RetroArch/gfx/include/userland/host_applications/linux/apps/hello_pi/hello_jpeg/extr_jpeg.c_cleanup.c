#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int inputBufferHeaderCount; int /*<<< orphan*/ * client; TYPE_2__* imageResizer; TYPE_1__* imageDecoder; int /*<<< orphan*/ * pOutputBufferHeader; int /*<<< orphan*/ ** ppInputBufferHeader; } ;
struct TYPE_6__ {int /*<<< orphan*/  component; int /*<<< orphan*/  inPort; int /*<<< orphan*/  handle; int /*<<< orphan*/  outPort; } ;
struct TYPE_5__ {int /*<<< orphan*/  component; int /*<<< orphan*/  outPort; int /*<<< orphan*/  handle; int /*<<< orphan*/  inPort; } ;
typedef  TYPE_3__ OPENMAX_JPEG_DECODER ;
typedef  int /*<<< orphan*/  OMX_BUFFERHEADERTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  OMX_CommandFlush ; 
 int /*<<< orphan*/  OMX_CommandPortDisable ; 
 int /*<<< orphan*/  OMX_CommandStateSet ; 
 int /*<<< orphan*/  OMX_Deinit () ; 
 int /*<<< orphan*/  OMX_EventCmdComplete ; 
 int /*<<< orphan*/  OMX_FreeBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OMX_SendCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OMX_SetupTunnel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OMX_StateIdle ; 
 int /*<<< orphan*/  OMX_StateLoaded ; 
 int /*<<< orphan*/  TIMEOUT_MS ; 
 int /*<<< orphan*/  ilclient_change_component_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilclient_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ilclient_wait_for_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
cleanup(OPENMAX_JPEG_DECODER * decoder)
{
    // flush everything through
    OMX_SendCommand(decoder->imageDecoder->handle,
		    OMX_CommandFlush, decoder->imageDecoder->outPort,
		    NULL);
    ilclient_wait_for_event(decoder->imageDecoder->component,
			    OMX_EventCmdComplete, OMX_CommandFlush, 0,
			    decoder->imageDecoder->outPort, 0, 0,
			    TIMEOUT_MS);
    OMX_SendCommand(decoder->imageResizer->handle, OMX_CommandFlush,
		    decoder->imageResizer->inPort, NULL);
    ilclient_wait_for_event(decoder->imageResizer->component,
			    OMX_EventCmdComplete, OMX_CommandFlush, 0,
			    decoder->imageResizer->inPort, 1, 0,
			    TIMEOUT_MS);

    OMX_SendCommand(decoder->imageDecoder->handle, OMX_CommandPortDisable,
		    decoder->imageDecoder->inPort, NULL);

    int             i = 0;
    for (i = 0; i < decoder->inputBufferHeaderCount; i++) {
	OMX_BUFFERHEADERTYPE *vpBufHeader =
	    decoder->ppInputBufferHeader[i];

	OMX_FreeBuffer(decoder->imageDecoder->handle,
		       decoder->imageDecoder->inPort, vpBufHeader);
    }

    ilclient_wait_for_event(decoder->imageDecoder->component,
			    OMX_EventCmdComplete, OMX_CommandPortDisable,
			    0, decoder->imageDecoder->inPort, 0, 0,
			    TIMEOUT_MS);

    OMX_SendCommand(decoder->imageResizer->handle, OMX_CommandPortDisable,
		    decoder->imageResizer->outPort, NULL);

    OMX_FreeBuffer(decoder->imageResizer->handle,
		   decoder->imageResizer->outPort,
		   decoder->pOutputBufferHeader);

    ilclient_wait_for_event(decoder->imageResizer->component,
			    OMX_EventCmdComplete, OMX_CommandPortDisable,
			    0, decoder->imageResizer->outPort, 0, 0,
			    TIMEOUT_MS);

    OMX_SendCommand(decoder->imageDecoder->handle, OMX_CommandPortDisable,
		    decoder->imageDecoder->outPort, NULL);
    ilclient_wait_for_event(decoder->imageDecoder->component,
			    OMX_EventCmdComplete, OMX_CommandPortDisable,
			    0, decoder->imageDecoder->outPort, 0, 0,
			    TIMEOUT_MS);

    OMX_SendCommand(decoder->imageResizer->handle, OMX_CommandPortDisable,
		    decoder->imageResizer->inPort, NULL);
    ilclient_wait_for_event(decoder->imageResizer->component,
			    OMX_EventCmdComplete, OMX_CommandPortDisable,
			    0, decoder->imageResizer->inPort, 0, 0,
			    TIMEOUT_MS);

    OMX_SetupTunnel(decoder->imageDecoder->handle,
		    decoder->imageDecoder->outPort, NULL, 0);
    OMX_SetupTunnel(decoder->imageResizer->handle,
		    decoder->imageResizer->inPort, NULL, 0);

    ilclient_change_component_state(decoder->imageDecoder->component,
				    OMX_StateIdle);
    ilclient_change_component_state(decoder->imageResizer->component,
				    OMX_StateIdle);

    ilclient_wait_for_event(decoder->imageDecoder->component,
			    OMX_EventCmdComplete, OMX_CommandStateSet, 0,
			    OMX_StateIdle, 0, 0, TIMEOUT_MS);
    ilclient_wait_for_event(decoder->imageResizer->component,
			    OMX_EventCmdComplete, OMX_CommandStateSet, 0,
			    OMX_StateIdle, 0, 0, TIMEOUT_MS);

    ilclient_change_component_state(decoder->imageDecoder->component,
				    OMX_StateLoaded);
    ilclient_change_component_state(decoder->imageResizer->component,
				    OMX_StateLoaded);

    ilclient_wait_for_event(decoder->imageDecoder->component,
			    OMX_EventCmdComplete, OMX_CommandStateSet, 0,
			    OMX_StateLoaded, 0, 0, TIMEOUT_MS);
    ilclient_wait_for_event(decoder->imageResizer->component,
			    OMX_EventCmdComplete, OMX_CommandStateSet, 0,
			    OMX_StateLoaded, 0, 0, TIMEOUT_MS);

    OMX_Deinit();

    if (decoder->client != NULL) {
	ilclient_destroy(decoder->client);
    }
}