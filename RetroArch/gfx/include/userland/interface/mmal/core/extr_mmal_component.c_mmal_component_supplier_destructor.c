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
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ MMAL_COMPONENT_SUPPLIER_T ;

/* Variables and functions */
 TYPE_1__* suppliers ; 
 int /*<<< orphan*/  vcos_free (TYPE_1__*) ; 

void mmal_component_supplier_destructor(void)
{
   MMAL_COMPONENT_SUPPLIER_T *supplier = suppliers;

   /* walk list of suppliers and free associated memory */
   while (supplier)
   {
      MMAL_COMPONENT_SUPPLIER_T *current = supplier;
      supplier = supplier->next;
      vcos_free(current);
   }
}