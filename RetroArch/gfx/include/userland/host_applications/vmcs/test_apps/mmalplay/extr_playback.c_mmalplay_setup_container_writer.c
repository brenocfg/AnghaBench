#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {unsigned int size; int /*<<< orphan*/  id; } ;
struct TYPE_9__ {char const* name; int /*<<< orphan*/  control; int /*<<< orphan*/  input_num; } ;
struct TYPE_8__ {TYPE_4__ hdr; int /*<<< orphan*/  uri; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_1__ MMAL_PARAMETER_URI_T ;
typedef  int /*<<< orphan*/  MMAL_PARAMETER_HEADER_T ;
typedef  TYPE_2__ MMAL_COMPONENT_T ;
typedef  int /*<<< orphan*/  MMALPLAY_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,...) ; 
 scalar_t__ MMAL_EINVAL ; 
 scalar_t__ MMAL_ENOMEM ; 
 int /*<<< orphan*/  MMAL_PARAMETER_URI ; 
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (int /*<<< orphan*/ *) ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (unsigned int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ mmal_port_parameter_set (int /*<<< orphan*/ ,TYPE_4__*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  vcos_safe_strcpy (int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_STATUS_T mmalplay_setup_container_writer(MMALPLAY_T *ctx,
   MMAL_COMPONENT_T *writer, const char *uri)
{
   MMAL_PARAMETER_URI_T *param = 0;
   unsigned int param_size;
   MMAL_STATUS_T status = MMAL_EINVAL;
   size_t uri_len;
   MMAL_PARAM_UNUSED(ctx);

   if(!writer->input_num)
   {
      LOG_ERROR("%s doesn't have input ports", writer->name);
      goto error;
   }

   /* Open the given URI */
   uri_len = strlen(uri);
   param_size = sizeof(MMAL_PARAMETER_HEADER_T) + uri_len;
   param = malloc(param_size);
   if(!param)
   {
      LOG_ERROR("out of memory");
      status = MMAL_ENOMEM;
      goto error;
   }
   memset(param, 0, param_size);
   param->hdr.id = MMAL_PARAMETER_URI;
   param->hdr.size = param_size;
   vcos_safe_strcpy(param->uri, uri, uri_len + 1, 0);
   status = mmal_port_parameter_set(writer->control, &param->hdr);
   if(status != MMAL_SUCCESS)
   {
      LOG_ERROR("could not open file %s", uri);
      goto error;
   }

 error:
   if(param)
      free(param);
   return status;
}