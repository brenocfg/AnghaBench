#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int MMAL_PORT_TYPE_T ;

/* Variables and functions */
#define  MMAL_PORT_TYPE_CLOCK 131 
#define  MMAL_PORT_TYPE_CONTROL 130 
#define  MMAL_PORT_TYPE_INPUT 129 
#define  MMAL_PORT_TYPE_OUTPUT 128 

const char* mmal_port_type_to_string(MMAL_PORT_TYPE_T type)
{
   const char *str;

   switch (type)
   {
   case MMAL_PORT_TYPE_INPUT:   str = "in";  break;
   case MMAL_PORT_TYPE_OUTPUT:  str = "out"; break;
   case MMAL_PORT_TYPE_CLOCK:   str = "clk"; break;
   case MMAL_PORT_TYPE_CONTROL: str = "ctr"; break;
   default:                     str = "invalid"; break;
   }

   return str;
}