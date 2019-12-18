#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_20__ {size_t tracks_num; TYPE_4__* priv; TYPE_3__** tracks; } ;
typedef  TYPE_5__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_21__ {int uri_has_network_info; char* comms_buffer; int /*<<< orphan*/  header_list; scalar_t__ cseq_value; int /*<<< orphan*/  next_rtp_port; TYPE_3__** tracks; } ;
typedef  TYPE_6__ VC_CONTAINER_MODULE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINERS_LIST_COMPARATOR_T ;
struct TYPE_19__ {int /*<<< orphan*/  pf_seek; int /*<<< orphan*/  pf_read; int /*<<< orphan*/  (* pf_close ) (TYPE_5__*) ;TYPE_1__* io; TYPE_6__* module; int /*<<< orphan*/  uri; } ;
struct TYPE_18__ {TYPE_2__* priv; } ;
struct TYPE_17__ {int /*<<< orphan*/  module; } ;
struct TYPE_16__ {int /*<<< orphan*/  uri; } ;
typedef  int /*<<< orphan*/  RTSP_HEADER_T ;

/* Variables and functions */
 scalar_t__ COMMS_BUFFER_SIZE ; 
 int /*<<< orphan*/  DATA_UNAVAILABLE_READ_TIMEOUT_MS ; 
 int /*<<< orphan*/  FIRST_DYNAMIC_PORT ; 
 int /*<<< orphan*/  HEADER_LIST_INITIAL_CAPACITY ; 
 int /*<<< orphan*/  LOG_DEBUG (TYPE_5__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  RTSP_NETWORK_URI_START ; 
 int /*<<< orphan*/  RTSP_NETWORK_URI_START_LENGTH ; 
 int /*<<< orphan*/  RTSP_PKT_SCHEME ; 
 int /*<<< orphan*/  RTSP_SCHEME ; 
 scalar_t__ STREAM_STATUS (TYPE_5__*) ; 
 int /*<<< orphan*/  VC_CONTAINER_CONTROL_IO_SET_READ_TIMEOUT_MS ; 
 scalar_t__ VC_CONTAINER_ERROR_EOS ; 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_INVALID ; 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 scalar_t__ VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ calloc (int,scalar_t__) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rtsp_describe (TYPE_5__*) ; 
 scalar_t__ rtsp_header_comparator ; 
 scalar_t__ rtsp_play (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsp_reader_close (TYPE_5__*) ; 
 int /*<<< orphan*/  rtsp_reader_read ; 
 int /*<<< orphan*/  rtsp_reader_seek ; 
 scalar_t__ rtsp_setup (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_container_control (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_containers_list_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_uri_scheme (int /*<<< orphan*/ ) ; 

VC_CONTAINER_STATUS_T rtsp_reader_open( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_MODULE_T *module = 0;
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   uint32_t ii;

   /* Check the URI scheme looks valid */
   if (!vc_uri_scheme(p_ctx->priv->uri) ||
       (strcasecmp(vc_uri_scheme(p_ctx->priv->uri), RTSP_SCHEME) &&
        strcasecmp(vc_uri_scheme(p_ctx->priv->uri), RTSP_PKT_SCHEME)))
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

   /* Allocate our context */
   if ((module = (VC_CONTAINER_MODULE_T *)malloc(sizeof(VC_CONTAINER_MODULE_T))) == NULL)
   {
      status = VC_CONTAINER_ERROR_OUT_OF_MEMORY;
      goto error;
   }

   memset(module, 0, sizeof(*module));
   p_ctx->priv->module = module;
   p_ctx->tracks = module->tracks;
   module->next_rtp_port = FIRST_DYNAMIC_PORT;
   module->cseq_value = 0;
   module->uri_has_network_info =
         (strncasecmp(p_ctx->priv->io->uri, RTSP_NETWORK_URI_START, RTSP_NETWORK_URI_START_LENGTH) == 0);
   module->comms_buffer = (char *)calloc(1, COMMS_BUFFER_SIZE+1);
   if (!module->comms_buffer) { status = VC_CONTAINER_ERROR_OUT_OF_MEMORY; goto error; }

   /* header_list will contain pointers into the response_buffer, so take care in re-use */
   module->header_list = vc_containers_list_create(HEADER_LIST_INITIAL_CAPACITY, sizeof(RTSP_HEADER_T),
         (VC_CONTAINERS_LIST_COMPARATOR_T)rtsp_header_comparator);
   if (!module->header_list) { status = VC_CONTAINER_ERROR_OUT_OF_MEMORY; goto error; }

   status = rtsp_describe(p_ctx);
   for (ii = 0; status == VC_CONTAINER_SUCCESS && ii < p_ctx->tracks_num; ii++)
      status = rtsp_setup(p_ctx, p_ctx->tracks[ii]->priv->module);
   for (ii = 0; status == VC_CONTAINER_SUCCESS && ii < p_ctx->tracks_num; ii++)
      status = rtsp_play(p_ctx, p_ctx->tracks[ii]->priv->module);
   if (status != VC_CONTAINER_SUCCESS)
      goto error;

   /* Set the RTSP stream to block briefly, to allow polling for closure as well as to avoid spinning CPU */
   vc_container_control(p_ctx, VC_CONTAINER_CONTROL_IO_SET_READ_TIMEOUT_MS, DATA_UNAVAILABLE_READ_TIMEOUT_MS);

   p_ctx->priv->pf_close = rtsp_reader_close;
   p_ctx->priv->pf_read = rtsp_reader_read;
   p_ctx->priv->pf_seek = rtsp_reader_seek;

   if(STREAM_STATUS(p_ctx) != VC_CONTAINER_SUCCESS) goto error;
   return VC_CONTAINER_SUCCESS;

error:
   if(status == VC_CONTAINER_SUCCESS || status == VC_CONTAINER_ERROR_EOS)
      status = VC_CONTAINER_ERROR_FORMAT_INVALID;
   LOG_DEBUG(p_ctx, "error opening RTSP stream (%i)", status);
   rtsp_reader_close(p_ctx);
   return status;
}