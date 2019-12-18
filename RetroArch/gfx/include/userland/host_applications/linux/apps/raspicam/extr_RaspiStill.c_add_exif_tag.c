#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int size; int /*<<< orphan*/  id; } ;
struct TYPE_8__ {TYPE_4__ hdr; scalar_t__ data; } ;
struct TYPE_7__ {int /*<<< orphan*/ * output; struct TYPE_7__* encoder_component; } ;
typedef  TYPE_1__ RASPISTILL_STATE ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PARAMETER_EXIF_T ;

/* Variables and functions */
 int MAX_EXIF_PAYLOAD_LENGTH ; 
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_PARAMETER_EXIF ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  mmal_port_parameter_set (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int /*<<< orphan*/  vcos_assert (TYPE_1__*) ; 

__attribute__((used)) static MMAL_STATUS_T add_exif_tag(RASPISTILL_STATE *state, const char *exif_tag)
{
   MMAL_STATUS_T status;
   MMAL_PARAMETER_EXIF_T *exif_param = (MMAL_PARAMETER_EXIF_T*)calloc(sizeof(MMAL_PARAMETER_EXIF_T) + MAX_EXIF_PAYLOAD_LENGTH, 1);

   vcos_assert(state);
   vcos_assert(state->encoder_component);

   // Check to see if the tag is present or is indeed a key=value pair.
   if (!exif_tag || strchr(exif_tag, '=') == NULL || strlen(exif_tag) > MAX_EXIF_PAYLOAD_LENGTH-1)
      return MMAL_EINVAL;

   exif_param->hdr.id = MMAL_PARAMETER_EXIF;

   strncpy((char*)exif_param->data, exif_tag, MAX_EXIF_PAYLOAD_LENGTH-1);

   exif_param->hdr.size = sizeof(MMAL_PARAMETER_EXIF_T) + strlen((char*)exif_param->data);

   status = mmal_port_parameter_set(state->encoder_component->output[0], &exif_param->hdr);

   free(exif_param);

   return status;
}