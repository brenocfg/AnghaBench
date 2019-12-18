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
typedef  scalar_t__ VC_CONTAINER_ES_TYPE_T ;
struct TYPE_2__ {scalar_t__ container_type; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  MMAL_ES_TYPE_T ;

/* Variables and functions */
 scalar_t__ VC_CONTAINER_ES_TYPE_UNKNOWN ; 
 TYPE_1__* es_type_table ; 

__attribute__((used)) static MMAL_ES_TYPE_T container_to_mmal_es_type(VC_CONTAINER_ES_TYPE_T type)
{
   unsigned int i;
   for(i = 0; es_type_table[i].container_type != VC_CONTAINER_ES_TYPE_UNKNOWN; i++)
      if(es_type_table[i].container_type == type)
         break;
   return es_type_table[i].type;
}