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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_4__ {unsigned int extradata_size; int /*<<< orphan*/ * extradata; int /*<<< orphan*/ * type; } ;
typedef  TYPE_1__ VC_CONTAINER_ES_FORMAT_T ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_ERROR_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

VC_CONTAINER_STATUS_T vc_container_format_copy( VC_CONTAINER_ES_FORMAT_T *p_out,
                                                VC_CONTAINER_ES_FORMAT_T *p_in,
                                                unsigned int extra_buffer_size)
{
   void *type = p_out->type;
   uint8_t *extradata = p_out->extradata;

   /* Check we have a sufficient buffer to copy the extra data */
   if(p_in->extradata_size > extra_buffer_size ||
      (p_in->extradata_size && !p_out->extradata))
      return VC_CONTAINER_ERROR_BUFFER_TOO_SMALL;

   *p_out->type = *p_in->type;
   *p_out = *p_in;
   p_out->type = type;
   p_out->extradata = extradata;
   if(p_in->extradata_size)
      memcpy(p_out->extradata, p_in->extradata, p_in->extradata_size);

   return VC_CONTAINER_SUCCESS;
}