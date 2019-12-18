#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* es; } ;
struct TYPE_7__ {TYPE_1__ format; int /*<<< orphan*/  extradata_size; int /*<<< orphan*/  es; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ MMAL_ES_FORMAT_T ;
typedef  TYPE_2__ MMAL_ES_FORMAT_PRIVATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRADATA_SIZE_DEFAULT ; 
 int /*<<< orphan*/  MMAL_ES_FORMAT_MAGIC ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* vcos_calloc (int,int,char*) ; 

MMAL_ES_FORMAT_T *mmal_format_alloc(void)
{
   MMAL_ES_FORMAT_PRIVATE_T *private;

   private = vcos_calloc(1, sizeof(*private), "mmal format");
   if(!private) return 0;
   memset(private, 0, sizeof(*private));

   private->magic = MMAL_ES_FORMAT_MAGIC;
   private->format.es = (void *)&private->es;
   private->extradata_size = EXTRADATA_SIZE_DEFAULT;

   return &private->format;
}