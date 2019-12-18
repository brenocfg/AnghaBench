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
struct TYPE_2__ {int /*<<< orphan*/  userdata; int /*<<< orphan*/  (* unlock_cb ) (unsigned int,int /*<<< orphan*/ ) ;scalar_t__ is_element; } ;
typedef  TYPE_1__ rcheevos_deactivate_t ;

/* Variables and functions */
 scalar_t__ strtol (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rcheevos_deactivate_number(void* userdata,
      const char* number, size_t length)
{
   rcheevos_deactivate_t* ud = (rcheevos_deactivate_t*)userdata;
   unsigned id              = 0;

   if (ud->is_element)
   {
      ud->is_element = 0;
      id             = (unsigned)strtol(number, NULL, 10);

      ud->unlock_cb(id, ud->userdata);
   }

   return 0;
}