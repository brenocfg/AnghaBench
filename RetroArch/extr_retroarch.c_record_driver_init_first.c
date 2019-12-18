#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct record_params {int dummy; } ;
struct TYPE_4__ {void* (* init ) (struct record_params const*) ;} ;
typedef  TYPE_1__ record_driver_t ;

/* Variables and functions */
 TYPE_1__** record_drivers ; 
 void* stub1 (struct record_params const*) ; 

__attribute__((used)) static bool record_driver_init_first(
      const record_driver_t **backend, void **data,
      const struct record_params *params)
{
   unsigned i;

   for (i = 0; record_drivers[i]; i++)
   {
      void *handle = record_drivers[i]->init(params);

      if (!handle)
         continue;

      *backend = record_drivers[i];
      *data = handle;
      return true;
   }

   return false;
}