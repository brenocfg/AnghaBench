#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  payload; scalar_t__ extra; } ;
typedef  TYPE_1__ VC_CONTAINER_TRACK_MODULE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_BITS_T ;
struct TYPE_5__ {int auxiliary_length; scalar_t__ dts_delta_length; scalar_t__ cts_delta_length; scalar_t__ index_length; scalar_t__ size_length; int /*<<< orphan*/  au_headers; } ;
typedef  TYPE_2__ MP4_PAYLOAD_T ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_CURRENT_POINTER (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BITS_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BITS_READ_U32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  BITS_SKIP_BYTES (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BITS_TO_BYTES (int /*<<< orphan*/ ) ; 
 scalar_t__ BITS_VALID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FORMAT_INVALID ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_new_rtp_packet(VC_CONTAINER_T *p_ctx,
      VC_CONTAINER_TRACK_MODULE_T *t_module)
{
   VC_CONTAINER_BITS_T *payload = &t_module->payload;
   MP4_PAYLOAD_T *extra = (MP4_PAYLOAD_T *)t_module->extra;
   VC_CONTAINER_BITS_T *au_headers = &extra->au_headers;

   /* There will be an AU header section if any of its fields are non-zero. */
   if (extra->size_length || extra->index_length || extra->cts_delta_length || extra->dts_delta_length)
   {
      uint32_t au_headers_length;

      /* Calculate how far to advance the payload, to get past the AU headers */
      au_headers_length = BITS_READ_U32(p_ctx, payload, 16, "AU headers length");
      au_headers_length = BITS_TO_BYTES(au_headers_length); /* Round up to bytes */

      /* Record where the AU headers are in the payload */
      BITS_INIT(p_ctx, au_headers, BITS_CURRENT_POINTER(p_ctx, payload), au_headers_length);
      BITS_SKIP_BYTES(p_ctx, &t_module->payload, au_headers_length, "Move payload past AU headers");
   }

   /* Skip the auxiliary section, if present */
   if (extra->auxiliary_length)
   {
      uint32_t auxiliary_data_size;

      auxiliary_data_size = BITS_READ_U32(p_ctx, payload, extra->auxiliary_length, "Auxiliary length");
      auxiliary_data_size = BITS_TO_BYTES(auxiliary_data_size); /* Round up to bytes */
      BITS_SKIP_BYTES(p_ctx, payload, auxiliary_data_size, "Auxiliary data");
   }

   return BITS_VALID(p_ctx, payload) ? VC_CONTAINER_SUCCESS : VC_CONTAINER_ERROR_FORMAT_INVALID;
}