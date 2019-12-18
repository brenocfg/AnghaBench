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
struct TYPE_3__ {char const* prefix; scalar_t__ (* create ) (char const*,int /*<<< orphan*/ *) ;struct TYPE_3__* next; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_COMPONENT_T ;
typedef  TYPE_1__ MMAL_COMPONENT_SUPPLIER_T ;

/* Variables and functions */
 scalar_t__ MMAL_ENOSYS ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  memcmp (char const*,char const*,size_t) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 scalar_t__ stub1 (char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* suppliers ; 

__attribute__((used)) static MMAL_STATUS_T mmal_component_supplier_create(const char *name, MMAL_COMPONENT_T *component)
{
   MMAL_COMPONENT_SUPPLIER_T *supplier = suppliers;
   MMAL_STATUS_T status = MMAL_ENOSYS;
   const char *dot = strchr(name, '.');
   size_t dot_size = dot ? dot - name : (int)strlen(name);

   /* walk list of suppliers to see if any can create this component */
   while (supplier)
   {
      if (strlen(supplier->prefix) == dot_size && !memcmp(supplier->prefix, name, dot_size))
      {
         status = supplier->create(name, component);
         if (status == MMAL_SUCCESS)
            break;
      }
      supplier = supplier->next;
   }
   return status;
}