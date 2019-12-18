#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_5__ {size_t num_queries; TYPE_1__* queries; } ;
typedef  TYPE_2__ VC_URI_PARTS_T ;
struct TYPE_4__ {char* name; char* value; } ;

/* Variables and functions */

void vc_uri_query( const VC_URI_PARTS_T *p_uri, uint32_t index, const char **p_name, const char **p_value )
{
   const char *name = NULL;
   const char *value = NULL;

   if (p_uri)
   {
      if (index < p_uri->num_queries)
      {
         name = p_uri->queries[index].name;
         value = p_uri->queries[index].value;
      }
   }

   if (p_name)
      *p_name = name;
   if (p_value)
      *p_value = value;
}