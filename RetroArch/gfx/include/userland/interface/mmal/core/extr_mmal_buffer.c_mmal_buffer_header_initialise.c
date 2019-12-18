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
struct TYPE_3__ {int /*<<< orphan*/ * type; int /*<<< orphan*/ * priv; } ;
typedef  TYPE_1__ MMAL_BUFFER_HEADER_T ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_PRIVATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int mmal_buffer_header_size (int /*<<< orphan*/ ) ; 

MMAL_BUFFER_HEADER_T *mmal_buffer_header_initialise(void *mem, unsigned int length)
{
   MMAL_BUFFER_HEADER_T *header;
   unsigned int header_size = mmal_buffer_header_size(0);

   if(length < header_size)
      return 0;

   memset(mem, 0, header_size);

   header = (MMAL_BUFFER_HEADER_T *)mem;
   header->type = (void *)&header[1];
   header->priv = (MMAL_BUFFER_HEADER_PRIVATE_T *)&header->type[1];
   return header;
}