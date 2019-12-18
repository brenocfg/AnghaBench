#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ extradata; } ;
struct TYPE_4__ {unsigned int extradata_size; scalar_t__ buffer; TYPE_1__ format; scalar_t__ extradata; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_ES_FORMAT_T ;
typedef  TYPE_2__ MMAL_ES_FORMAT_PRIVATE_T ;

/* Variables and functions */
 unsigned int EXTRADATA_SIZE_MAX ; 
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_ENOMEM ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 scalar_t__ vcos_calloc (int,unsigned int,char*) ; 
 int /*<<< orphan*/  vcos_free (scalar_t__) ; 

MMAL_STATUS_T mmal_format_extradata_alloc(MMAL_ES_FORMAT_T *format, unsigned int size)
{
   MMAL_ES_FORMAT_PRIVATE_T *private = (MMAL_ES_FORMAT_PRIVATE_T *)format;

   /* Sanity check the size requested */
   if(size > EXTRADATA_SIZE_MAX)
      return MMAL_EINVAL;

   /* Allocate memory if needed */
   if(private->extradata_size < size)
   {
      if(private->extradata) vcos_free(private->extradata);
      private->extradata = vcos_calloc(1, size, "mmal format extradata");
      if(!private->extradata)
         return MMAL_ENOMEM;
      private->extradata_size = size;
   }

   /* Set the fields in the actual format structure */
   if(private->extradata) private->format.extradata = private->extradata;
   else private->format.extradata = private->buffer;

   return MMAL_SUCCESS;
}