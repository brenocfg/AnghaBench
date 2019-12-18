#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  const VC_URI_PARTS_T ;

/* Variables and functions */
 int /*<<< orphan*/  vc_uri_add_query (int /*<<< orphan*/  const*,char const*,char const*) ; 
 scalar_t__ vc_uri_num_queries (int /*<<< orphan*/  const*) ; 
 char* vc_uri_path (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  vc_uri_query (int /*<<< orphan*/  const*,scalar_t__,char const**,char const**) ; 
 int /*<<< orphan*/  vc_uri_set_path (int /*<<< orphan*/  const*,char const*) ; 

__attribute__((used)) static bool vc_uri_copy_base_path( const VC_URI_PARTS_T *base_uri,
      VC_URI_PARTS_T *relative_uri )
{
   const char *base_path = vc_uri_path(base_uri);

   /* No path set (or empty), copy from base */
   if (!vc_uri_set_path(relative_uri, base_path))
      return false;

   /* If relative path has no queries, copy base queries across */
   if (!vc_uri_num_queries(relative_uri))
   {
      uint32_t base_queries = vc_uri_num_queries(base_uri);
      const char *name, *value;
      uint32_t ii;

      for (ii = 0; ii < base_queries; ii++)
      {
         vc_uri_query(base_uri, ii, &name, &value);
         if (!vc_uri_add_query(relative_uri, name, value))
            return false;
      }
   }

   return true;
}