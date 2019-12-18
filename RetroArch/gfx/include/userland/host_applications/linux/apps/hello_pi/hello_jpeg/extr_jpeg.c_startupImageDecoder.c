#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {void* nVersion; } ;
struct TYPE_16__ {int nSize; int /*<<< orphan*/  eCompressionFormat; int /*<<< orphan*/  nPortIndex; TYPE_1__ nVersion; } ;
struct TYPE_12__ {void* nVersion; } ;
struct TYPE_15__ {int nSize; int nBufferCountActual; int /*<<< orphan*/  nBufferSize; int /*<<< orphan*/  nPortIndex; TYPE_2__ nVersion; } ;
struct TYPE_14__ {int inputBufferHeaderCount; TYPE_3__* imageDecoder; int /*<<< orphan*/ ** ppInputBufferHeader; } ;
struct TYPE_13__ {int /*<<< orphan*/  component; int /*<<< orphan*/  handle; int /*<<< orphan*/  inPort; } ;
typedef  TYPE_4__ OPENMAX_JPEG_DECODER ;
typedef  TYPE_5__ OMX_PARAM_PORTDEFINITIONTYPE ;
typedef  TYPE_6__ OMX_IMAGE_PARAM_PORTFORMATTYPE ;
typedef  int /*<<< orphan*/  OMX_BUFFERHEADERTYPE ;

/* Variables and functions */
 int OMXJPEG_ERROR_EXECUTING ; 
 int OMXJPEG_ERROR_MEMORY ; 
 int OMXJPEG_OK ; 
 scalar_t__ OMX_AllocateBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OMX_CommandPortEnable ; 
 int /*<<< orphan*/  OMX_CommandStateSet ; 
 scalar_t__ OMX_ErrorNone ; 
 int /*<<< orphan*/  OMX_EventCmdComplete ; 
 int /*<<< orphan*/  OMX_GetParameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  OMX_IMAGE_CodingJPEG ; 
 int /*<<< orphan*/  OMX_IndexParamImagePortFormat ; 
 int /*<<< orphan*/  OMX_IndexParamPortDefinition ; 
 int OMX_SendCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OMX_SetParameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  OMX_StateExecuting ; 
 int /*<<< orphan*/  OMX_StateIdle ; 
 void* OMX_VERSION ; 
 int /*<<< orphan*/  TIMEOUT_MS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ilclient_change_component_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ilclient_wait_for_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 

int
startupImageDecoder(OPENMAX_JPEG_DECODER * decoder)
{
    // move to idle
    ilclient_change_component_state(decoder->imageDecoder->component,
				    OMX_StateIdle);

    // set input image format
    OMX_IMAGE_PARAM_PORTFORMATTYPE imagePortFormat;
    memset(&imagePortFormat, 0, sizeof(OMX_IMAGE_PARAM_PORTFORMATTYPE));
    imagePortFormat.nSize = sizeof(OMX_IMAGE_PARAM_PORTFORMATTYPE);
    imagePortFormat.nVersion.nVersion = OMX_VERSION;
    imagePortFormat.nPortIndex = decoder->imageDecoder->inPort;
    imagePortFormat.eCompressionFormat = OMX_IMAGE_CodingJPEG;
    OMX_SetParameter(decoder->imageDecoder->handle,
		     OMX_IndexParamImagePortFormat, &imagePortFormat);

    // get buffer requirements
    OMX_PARAM_PORTDEFINITIONTYPE portdef;
    portdef.nSize = sizeof(OMX_PARAM_PORTDEFINITIONTYPE);
    portdef.nVersion.nVersion = OMX_VERSION;
    portdef.nPortIndex = decoder->imageDecoder->inPort;
    OMX_GetParameter(decoder->imageDecoder->handle,
		     OMX_IndexParamPortDefinition, &portdef);

    // enable the port and setup the buffers
    OMX_SendCommand(decoder->imageDecoder->handle,
		    OMX_CommandPortEnable,
		    decoder->imageDecoder->inPort, NULL);
    decoder->inputBufferHeaderCount = portdef.nBufferCountActual;
    // allocate pointer array
    decoder->ppInputBufferHeader =
	(OMX_BUFFERHEADERTYPE **) malloc(sizeof(void) *
					 decoder->inputBufferHeaderCount);
    // allocate each buffer
    int             i;
    for (i = 0; i < decoder->inputBufferHeaderCount; i++) {
	if (OMX_AllocateBuffer(decoder->imageDecoder->handle,
			       &decoder->ppInputBufferHeader[i],
			       decoder->imageDecoder->inPort,
			       (void *) i,
			       portdef.nBufferSize) != OMX_ErrorNone) {
	    perror("Allocate decode buffer");
	    return OMXJPEG_ERROR_MEMORY;
	}
    }
    // wait for port enable to complete - which it should once buffers are
    // assigned
    int             ret =
	ilclient_wait_for_event(decoder->imageDecoder->component,
				OMX_EventCmdComplete,
				OMX_CommandPortEnable, 0,
				decoder->imageDecoder->inPort, 0,
				0, TIMEOUT_MS);
    if (ret != 0) {
	fprintf(stderr, "Did not get port enable %d\n", ret);
	return OMXJPEG_ERROR_EXECUTING;
    }
    // start executing the decoder
    ret = OMX_SendCommand(decoder->imageDecoder->handle,
			  OMX_CommandStateSet, OMX_StateExecuting, NULL);
    if (ret != 0) {
	fprintf(stderr, "Error starting image decoder %x\n", ret);
	return OMXJPEG_ERROR_EXECUTING;
    }
    ret = ilclient_wait_for_event(decoder->imageDecoder->component,
				  OMX_EventCmdComplete,
				  OMX_StateExecuting, 0, 0, 1, 0,
				  TIMEOUT_MS);
    if (ret != 0) {
	fprintf(stderr, "Did not receive executing stat %d\n", ret);
	// return OMXJPEG_ERROR_EXECUTING;
    }

    return OMXJPEG_OK;
}