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
struct TYPE_2__ {scalar_t__ type; scalar_t__ domain; } ;
typedef  scalar_t__ OMX_PORTDOMAINTYPE ;
typedef  scalar_t__ MMAL_ES_TYPE_T ;

/* Variables and functions */
 scalar_t__ MMAL_ES_TYPE_UNKNOWN ; 
 TYPE_1__* mmal_omx_es_type_table ; 

MMAL_ES_TYPE_T mmalil_omx_domain_to_es_type(OMX_PORTDOMAINTYPE domain)
{
   unsigned int i;
   for(i = 0; mmal_omx_es_type_table[i].type != MMAL_ES_TYPE_UNKNOWN; i++)
      if(mmal_omx_es_type_table[i].domain == domain) break;
   return mmal_omx_es_type_table[i].type;
}