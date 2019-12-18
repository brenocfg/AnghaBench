#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_17__ {int is_enabled; TYPE_1__* priv; } ;
typedef  TYPE_3__ VC_CONTAINER_TRACK_T ;
struct TYPE_18__ {scalar_t__ timestamp_clock; scalar_t__ probation; scalar_t__ max_seq_num; int /*<<< orphan*/  flags; int /*<<< orphan*/  expected_ssrc; scalar_t__ payload_handler; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_4__ VC_CONTAINER_TRACK_MODULE_T ;
struct TYPE_19__ {int tracks_num; TYPE_2__* priv; TYPE_3__** tracks; } ;
typedef  TYPE_5__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_20__ {TYPE_3__* track; } ;
typedef  TYPE_6__ VC_CONTAINER_MODULE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINERS_LIST_T ;
struct TYPE_16__ {int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_seek; int /*<<< orphan*/  pf_read; int /*<<< orphan*/  (* pf_close ) (TYPE_5__*) ;TYPE_6__* module; int /*<<< orphan*/  uri; } ;
struct TYPE_15__ {TYPE_4__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (TYPE_5__*,char*,scalar_t__) ; 
 scalar_t__ MAXIMUM_PACKET_SIZE ; 
 scalar_t__ MIN_SEQUENTIAL ; 
 int /*<<< orphan*/  PAYLOAD_TYPE_NAME ; 
 int /*<<< orphan*/  RTP_PKT_SCHEME ; 
 int /*<<< orphan*/  RTP_SCHEME ; 
 int /*<<< orphan*/  SEQ_NAME ; 
 int /*<<< orphan*/  SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSRC_NAME ; 
 int /*<<< orphan*/  TRACK_SSRC_SET ; 
 scalar_t__ VC_CONTAINER_ERROR_EOS ; 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_INVALID ; 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 scalar_t__ VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ decode_payload_type (TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * fill_parameter_list (int /*<<< orphan*/ ) ; 
 scalar_t__ generic_payload_handler ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rtp_get_parameter_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ rtp_get_parameter_x32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtp_reader_close (TYPE_5__*) ; 
 int /*<<< orphan*/  rtp_reader_control ; 
 int /*<<< orphan*/  rtp_reader_read ; 
 int /*<<< orphan*/  rtp_reader_seek ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* vc_container_allocate_track (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  vc_container_assert (int) ; 
 int /*<<< orphan*/  vc_containers_list_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_uri_scheme (int /*<<< orphan*/ ) ; 

VC_CONTAINER_STATUS_T rtp_reader_open( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_MODULE_T *module = 0;
   VC_CONTAINER_TRACK_T *track = 0;
   VC_CONTAINER_TRACK_MODULE_T *t_module = 0;
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   VC_CONTAINERS_LIST_T *parameters = NULL;
   uint32_t payload_type;
   uint32_t initial_seq_num;

   /* Check the URI scheme looks valid */
   if (!vc_uri_scheme(p_ctx->priv->uri) ||
       (strcasecmp(vc_uri_scheme(p_ctx->priv->uri), RTP_SCHEME) &&
        strcasecmp(vc_uri_scheme(p_ctx->priv->uri), RTP_PKT_SCHEME)))
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

   /* Make the query/parameter list more easily searchable */
   parameters = fill_parameter_list(p_ctx->priv->uri);
   if (!parameters) { status = VC_CONTAINER_ERROR_OUT_OF_MEMORY; goto error; }

   /* Payload type parameter is mandatory and must fit in 7 bits */
   if (!rtp_get_parameter_u32(parameters, PAYLOAD_TYPE_NAME, &payload_type) || payload_type > 127)
   {
      status = VC_CONTAINER_ERROR_FORMAT_INVALID;
      goto error;
   }

   /* Allocate our context */
   module = (VC_CONTAINER_MODULE_T *)malloc(sizeof(VC_CONTAINER_MODULE_T));
   if (!module) { status = VC_CONTAINER_ERROR_OUT_OF_MEMORY; goto error; }

   memset(module, 0, sizeof(*module));
   p_ctx->priv->module = module;
   p_ctx->tracks = &module->track;

   /* Allocate the track, including space for reading an RTP packet on the end */
   track = vc_container_allocate_track(p_ctx, sizeof(VC_CONTAINER_TRACK_MODULE_T) + MAXIMUM_PACKET_SIZE);
   if (!track)
   {
      status = VC_CONTAINER_ERROR_OUT_OF_MEMORY;
      goto error;
   }
   module->track = track;
   p_ctx->tracks_num = 1;
   t_module = track->priv->module;

   /* Initialise the track data */
   t_module->buffer = (uint8_t *)(t_module + 1);
   status = decode_payload_type(p_ctx, track, parameters, payload_type);
   if (status != VC_CONTAINER_SUCCESS)
      goto error;

   vc_container_assert(t_module->timestamp_clock != 0);

   /* Default to a generic, unstructured payload handler */
   if (!t_module->payload_handler)
      t_module->payload_handler = generic_payload_handler;

   if (rtp_get_parameter_x32(parameters, SSRC_NAME, &t_module->expected_ssrc))
      SET_BIT(t_module->flags, TRACK_SSRC_SET);

   t_module->probation = MIN_SEQUENTIAL;
   if (rtp_get_parameter_u32(parameters, SEQ_NAME, &initial_seq_num))
   {
      /* If an initial sequence number is provided, avoid probation period */
      t_module->max_seq_num = (uint16_t)initial_seq_num;
      t_module->probation = 0;
   }

   track->is_enabled = true;

   vc_containers_list_destroy(parameters);

   p_ctx->priv->pf_close = rtp_reader_close;
   p_ctx->priv->pf_read = rtp_reader_read;
   p_ctx->priv->pf_seek = rtp_reader_seek;
   p_ctx->priv->pf_control = rtp_reader_control;

   return VC_CONTAINER_SUCCESS;

error:
   if (parameters) vc_containers_list_destroy(parameters);
   if(status == VC_CONTAINER_SUCCESS || status == VC_CONTAINER_ERROR_EOS)
      status = VC_CONTAINER_ERROR_FORMAT_INVALID;
   LOG_DEBUG(p_ctx, "error opening RTP (%i)", status);
   rtp_reader_close(p_ctx);
   return status;
}