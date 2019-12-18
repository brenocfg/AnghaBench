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
struct TYPE_3__ {int (* parse_drive_list ) (void*,int) ;} ;
typedef  TYPE_1__ frontend_ctx_driver_t ;

/* Variables and functions */
 TYPE_1__* frontend_get_ptr () ; 
 int stub1 (void*,int) ; 

int frontend_driver_parse_drive_list(void *data, bool load_content)
{
   frontend_ctx_driver_t *frontend = frontend_get_ptr();

   if (!frontend || !frontend->parse_drive_list)
      return -1;
   return frontend->parse_drive_list(data, load_content);
}