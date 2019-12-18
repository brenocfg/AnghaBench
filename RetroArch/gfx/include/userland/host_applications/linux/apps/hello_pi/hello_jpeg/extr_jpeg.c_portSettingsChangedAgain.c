#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  nVersion; } ;
struct TYPE_13__ {int nSize; int /*<<< orphan*/  nPortIndex; TYPE_1__ nVersion; } ;
struct TYPE_12__ {TYPE_3__* imageResizer; TYPE_2__* imageDecoder; } ;
struct TYPE_11__ {int /*<<< orphan*/  outPort; int /*<<< orphan*/  component; int /*<<< orphan*/  inPort; int /*<<< orphan*/  handle; } ;
struct TYPE_10__ {int /*<<< orphan*/  outPort; int /*<<< orphan*/  component; int /*<<< orphan*/  handle; } ;
typedef  TYPE_4__ OPENMAX_JPEG_DECODER ;
typedef  TYPE_5__ OMX_PARAM_PORTDEFINITIONTYPE ;

/* Variables and functions */
 int OMXJPEG_OK ; 
 int /*<<< orphan*/  OMX_EventPortSettingsChanged ; 
 int /*<<< orphan*/  OMX_GetParameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  OMX_IndexParamPortDefinition ; 
 int /*<<< orphan*/  OMX_SetParameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  OMX_VERSION ; 
 int /*<<< orphan*/  TIMEOUT_MS ; 
 int /*<<< orphan*/  ilclient_disable_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilclient_enable_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilclient_wait_for_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
portSettingsChangedAgain(OPENMAX_JPEG_DECODER * decoder)
{
    ilclient_disable_port(decoder->imageDecoder->component,
			  decoder->imageDecoder->outPort);
    ilclient_disable_port(decoder->imageResizer->component,
			  decoder->imageResizer->inPort);

    OMX_PARAM_PORTDEFINITIONTYPE portdef;

    // need to setup the input for the resizer with the output of the
    // decoder
    portdef.nSize = sizeof(OMX_PARAM_PORTDEFINITIONTYPE);
    portdef.nVersion.nVersion = OMX_VERSION;
    portdef.nPortIndex = decoder->imageDecoder->outPort;
    OMX_GetParameter(decoder->imageDecoder->handle,
		     OMX_IndexParamPortDefinition, &portdef);

    // tell resizer input what the decoder output will be providing
    portdef.nPortIndex = decoder->imageResizer->inPort;
    OMX_SetParameter(decoder->imageResizer->handle,
		     OMX_IndexParamPortDefinition, &portdef);

    // enable output of decoder and input of resizer (ie enable tunnel)
    ilclient_enable_port(decoder->imageDecoder->component,
			 decoder->imageDecoder->outPort);
    ilclient_enable_port(decoder->imageResizer->component,
			 decoder->imageResizer->inPort);

    // need to wait for this event
    ilclient_wait_for_event(decoder->imageResizer->component,
			    OMX_EventPortSettingsChanged,
			    decoder->imageResizer->outPort, 1,
			    0, 0, 0, TIMEOUT_MS);

    return OMXJPEG_OK;
}