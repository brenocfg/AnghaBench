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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  VC_URI_QUERY_T ;
struct TYPE_4__ {int /*<<< orphan*/ * queries; } ;
typedef  TYPE_1__ VC_URI_PARTS_T ;

/* Variables and functions */
 scalar_t__ malloc (size_t) ; 
 int store_query (TYPE_1__*,char const*,char const*,char const*) ; 

__attribute__((used)) static bool parse_query( VC_URI_PARTS_T *p_uri, const char *str, uint32_t str_len )
{
   uint32_t ii;
   uint32_t query_count;
   VC_URI_QUERY_T *queries;
   const char *name_start = str;
   const char *equals_ptr = NULL;
   char c;

   if (!str_len)
      return true;

   /* Scan for the number of query items, so array can be allocated the right size */
   query_count = 1;  /* At least */
   for (ii = 0; ii < str_len; ii++)
   {
      c = str[ii];

      if (c == '&' || c ==';')
         query_count++;
   }

   queries = (VC_URI_QUERY_T *)malloc(query_count * sizeof(VC_URI_QUERY_T));
   if (!queries)
      return false;

   p_uri->queries = queries;

   /* Go back and parse the string for each query item and store in array */
   for (ii = 0; ii < str_len; ii++)
   {
      c = *str;

      /* Take first '=' as break between name and value */
      if (c == '=' && !equals_ptr)
         equals_ptr = str;

      /* If at the end of the name or name/value pair */
      if (c == '&' || c ==';')
      {
         if (!store_query(p_uri, name_start, equals_ptr, str))
            return false;

         equals_ptr = NULL;
         name_start = str + 1;
      }

      str++;
   }

   return store_query(p_uri, name_start, equals_ptr, str);
}