#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char const* str; scalar_t__ status; } ;
typedef  scalar_t__ MMAL_STATUS_T ;

/* Variables and functions */
 TYPE_1__* status_to_string_map ; 

const char *mmal_status_to_string(MMAL_STATUS_T status)
{
   unsigned i;

   for (i=0; status_to_string_map[i].str; i++)
      if (status_to_string_map[i].status == status)
         break;

   return status_to_string_map[i].str ? status_to_string_map[i].str : "UNKNOWN";
}