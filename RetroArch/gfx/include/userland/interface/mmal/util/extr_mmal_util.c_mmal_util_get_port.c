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
struct TYPE_3__ {unsigned int input_num; unsigned int output_num; unsigned int clock_num; int /*<<< orphan*/ * control; int /*<<< orphan*/ ** clock; int /*<<< orphan*/ ** output; int /*<<< orphan*/ ** input; } ;
typedef  int MMAL_PORT_TYPE_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;
typedef  TYPE_1__ MMAL_COMPONENT_T ;

/* Variables and functions */
#define  MMAL_PORT_TYPE_CLOCK 131 
#define  MMAL_PORT_TYPE_CONTROL 130 
#define  MMAL_PORT_TYPE_INPUT 129 
#define  MMAL_PORT_TYPE_OUTPUT 128 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 

MMAL_PORT_T *mmal_util_get_port(MMAL_COMPONENT_T *comp, MMAL_PORT_TYPE_T type, unsigned index)
{
   unsigned num;
   MMAL_PORT_T **list;

   switch (type)
   {
   case MMAL_PORT_TYPE_INPUT:
      num = comp->input_num;
      list = comp->input;
      break;

   case MMAL_PORT_TYPE_OUTPUT:
      num = comp->output_num;
      list = comp->output;
      break;

   case MMAL_PORT_TYPE_CLOCK:
      num = comp->clock_num;
      list = comp->clock;
      break;

   case MMAL_PORT_TYPE_CONTROL:
      num = 1;
      list = &comp->control;
      break;

   default:
      vcos_assert(0);
      return NULL;
   }
   if (index < num)
      /* coverity[ptr_arith] num is 1 here */
      return list[index];
   else
      return NULL;
}