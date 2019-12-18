#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ magic; struct TYPE_3__* extradata; } ;
typedef  int /*<<< orphan*/  MMAL_ES_FORMAT_T ;
typedef  TYPE_1__ MMAL_ES_FORMAT_PRIVATE_T ;

/* Variables and functions */
 scalar_t__ MMAL_ES_FORMAT_MAGIC ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_free (TYPE_1__*) ; 

void mmal_format_free(MMAL_ES_FORMAT_T *format)
{
   MMAL_ES_FORMAT_PRIVATE_T *private = (MMAL_ES_FORMAT_PRIVATE_T *)format;
   vcos_assert(private->magic == MMAL_ES_FORMAT_MAGIC);
   if(private->extradata) vcos_free(private->extradata);
   vcos_free(private);
}