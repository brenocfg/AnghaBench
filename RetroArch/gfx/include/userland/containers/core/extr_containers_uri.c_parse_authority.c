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
typedef  int uint32_t ;
struct TYPE_3__ {void* port; void* host; void* userinfo; } ;
typedef  TYPE_1__ VC_URI_PARTS_T ;

/* Variables and functions */
 void* create_unescaped_string (char const*,int) ; 
 int /*<<< orphan*/  to_lower_string (void*) ; 

__attribute__((used)) static bool parse_authority( VC_URI_PARTS_T *p_uri, const char *str,
      uint32_t str_len, const char *userinfo_end )
{
   const char *marker = userinfo_end;
   const char *str_end = str + str_len;
   char c;

   if (marker)
   {
      p_uri->userinfo = create_unescaped_string(str, marker - str);
      if (!p_uri->userinfo)
         return false;
      str = marker + 1; /* Past '@' character */
   }

   if (*str == '[')     /* IPvFuture / IPv6 address */
   {
      /* Find end of address marker */
      for (marker = str; marker < str_end; marker++)
      {
         c = *marker;
         if (c == ']')
            break;
      }

      if (marker < str_end)
         marker++;   /* Found marker, move to next character */
   } else {
      /* Find port value marker*/
      for (marker = str; marker < str_end; marker++)
      {
         c = *marker;
         if (c == ':')
            break;
      }
   }

   /* Always store the host, even if empty, to trigger the "://" form of URI */
   p_uri->host = create_unescaped_string(str, marker - str);
   if (!p_uri->host)
      return false;
   to_lower_string(p_uri->host);    /* Host names are case-insensitive */

   if (*marker == ':')
   {
      str = marker + 1;
      p_uri->port = create_unescaped_string(str, str_end - str);
      if (!p_uri->port)
         return false;
   }

   return true;
}