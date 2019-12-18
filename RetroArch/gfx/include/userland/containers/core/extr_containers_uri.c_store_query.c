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
typedef  int uint32_t ;
struct TYPE_4__ {char* name; char* value; } ;
typedef  TYPE_1__ VC_URI_QUERY_T ;
struct TYPE_5__ {int /*<<< orphan*/  num_queries; TYPE_1__* queries; } ;
typedef  TYPE_2__ VC_URI_PARTS_T ;

/* Variables and functions */
 char* create_unescaped_string (char const*,int) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static bool store_query( VC_URI_PARTS_T *p_uri, const char *name_start,
      const char *equals_ptr, const char *query_end)
{
   uint32_t name_len, value_len;

   if (equals_ptr)
   {
      name_len = equals_ptr - name_start;
      value_len = query_end - equals_ptr - 1;   /* Don't include '=' itself */
   } else {
      name_len = query_end - name_start;
      value_len = 0;
   }

   /* Only store something if there is a name */
   if (name_len)
   {
      char *name, *value = NULL;
      VC_URI_QUERY_T *p_query;

      if (equals_ptr)
      {
         value = create_unescaped_string(equals_ptr + 1, value_len);
         if (!value)
            return false;
         equals_ptr = query_end;
      }

      name = create_unescaped_string(name_start, name_len);
      if (!name)
      {
         if (value)
            free(value);
         return false;
      }

      /* Store query data in URI structure */
      p_query = &p_uri->queries[ p_uri->num_queries++ ];
      p_query->name = name;
      p_query->value = value;
   }

   return true;
}