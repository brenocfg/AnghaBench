#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * client; } ;
typedef  TYPE_1__ OPENMAX_JPEG_DECODER ;

/* Variables and functions */
 int OMXJPEG_ERROR_ILCLIENT_INIT ; 
 int OMXJPEG_ERROR_MEMORY ; 
 int OMXJPEG_ERROR_OMX_INIT ; 
 int OMXJPEG_OK ; 
 scalar_t__ OMX_ErrorNone ; 
 scalar_t__ OMX_Init () ; 
 int /*<<< orphan*/  ilclient_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ilclient_init () ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int prepareImageDecoder (TYPE_1__*) ; 
 int prepareResizer (TYPE_1__*) ; 
 int startupImageDecoder (TYPE_1__*) ; 

int
setupOpenMaxJpegDecoder(OPENMAX_JPEG_DECODER ** pDecoder)
{
    *pDecoder = malloc(sizeof(OPENMAX_JPEG_DECODER));
    if (pDecoder[0] == NULL) {
	perror("malloc decoder");
	return OMXJPEG_ERROR_MEMORY;
    }
    memset(*pDecoder, 0, sizeof(OPENMAX_JPEG_DECODER));

    if ((pDecoder[0]->client = ilclient_init()) == NULL) {
	perror("ilclient_init");
	return OMXJPEG_ERROR_ILCLIENT_INIT;
    }

    if (OMX_Init() != OMX_ErrorNone) {
	ilclient_destroy(pDecoder[0]->client);
	perror("OMX_Init");
	return OMXJPEG_ERROR_OMX_INIT;
    }
    // prepare the image decoder
    int             ret = prepareImageDecoder(pDecoder[0]);
    if (ret != OMXJPEG_OK)
	return ret;

    ret = prepareResizer(pDecoder[0]);
    if (ret != OMXJPEG_OK)
	return ret;

    ret = startupImageDecoder(pDecoder[0]);
    if (ret != OMXJPEG_OK)
	return ret;

    return OMXJPEG_OK;
}