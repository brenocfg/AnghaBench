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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ value; scalar_t__ name; } ;
typedef  TYPE_1__ VC_URI_QUERY_T ;
struct TYPE_5__ {scalar_t__ fragment; TYPE_1__* queries; scalar_t__ num_queries; scalar_t__ path; scalar_t__ port; scalar_t__ userinfo; scalar_t__ host; scalar_t__ scheme; } ;
typedef  TYPE_2__ VC_URI_PARTS_T ;

/* Variables and functions */
 scalar_t__ escaped_length (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fragment_reserved_chars ; 
 int /*<<< orphan*/  host_reserved_chars ; 
 int /*<<< orphan*/  path_reserved_chars ; 
 int /*<<< orphan*/  port_reserved_chars ; 
 int /*<<< orphan*/  query_reserved_chars ; 
 int /*<<< orphan*/  scheme_reserved_chars ; 
 scalar_t__ strlen (scalar_t__) ; 
 int /*<<< orphan*/  userinfo_reserved_chars ; 

__attribute__((used)) static uint32_t calculate_uri_length(const VC_URI_PARTS_T *p_uri)
{
   uint32_t length = 0;
   uint32_t count;

   /* With no scheme, assume this is a plain path (without escaping) */
   if (!p_uri->scheme)
      return p_uri->path ? strlen(p_uri->path) : 0;

   length += escaped_length(p_uri->scheme, scheme_reserved_chars);
   length++; /* for the colon */

   if (p_uri->host)
   {
      length += escaped_length(p_uri->host, host_reserved_chars) + 2;  /* for the double slash */
      if (p_uri->userinfo)
         length += escaped_length(p_uri->userinfo, userinfo_reserved_chars) + 1; /* for the '@' */
      if (p_uri->port)
         length += escaped_length(p_uri->port, port_reserved_chars) + 1;     /* for the ':' */
   }

   if (p_uri->path)
      length += escaped_length(p_uri->path, path_reserved_chars);

   count = p_uri->num_queries;
   if (count)
   {
      VC_URI_QUERY_T * queries = p_uri->queries;

      while (count--)
      {
         /* The name is preceded by either the '?' or the '&' */
         length += escaped_length(queries->name, query_reserved_chars) + 1;

         /* The value is optional, but if present will require an '=' */
         if (queries->value)
            length += escaped_length(queries->value, query_reserved_chars) + 1;
         queries++;
      }
   }

   if (p_uri->fragment)
      length += escaped_length(p_uri->fragment, fragment_reserved_chars) + 1; /* for the '#' */

   return length;
}