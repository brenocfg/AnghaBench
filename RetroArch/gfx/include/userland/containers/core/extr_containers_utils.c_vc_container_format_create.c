#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_8__ {void* type; } ;
typedef  TYPE_1__ VC_CONTAINER_ES_FORMAT_T ;
struct TYPE_9__ {TYPE_1__ format; int /*<<< orphan*/  extradata_size; int /*<<< orphan*/  type; int /*<<< orphan*/  magic; } ;
typedef  TYPE_2__ VC_CONTAINER_ES_FORMAT_PRIVATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRADATA_SIZE_DEFAULT ; 
 int /*<<< orphan*/  VC_CONTAINER_ES_FORMAT_MAGIC ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vc_container_format_extradata_alloc (TYPE_1__*,unsigned int) ; 

VC_CONTAINER_ES_FORMAT_T *vc_container_format_create(unsigned int extradata_size)
{
   VC_CONTAINER_ES_FORMAT_PRIVATE_T *private;
   VC_CONTAINER_STATUS_T status;

   private = malloc(sizeof(*private));
   if(!private) return 0;
   memset(private, 0, sizeof(*private));

   private->magic = VC_CONTAINER_ES_FORMAT_MAGIC;
   private->format.type = (void *)&private->type;
   private->extradata_size = EXTRADATA_SIZE_DEFAULT;

   status = vc_container_format_extradata_alloc(&private->format, extradata_size);
   if(status != VC_CONTAINER_SUCCESS)
   {
      free(private);
      return NULL;
   }

   return &private->format;
}