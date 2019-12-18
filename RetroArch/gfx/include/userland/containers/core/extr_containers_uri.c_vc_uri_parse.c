#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {void* fragment; void* path; void* scheme; } ;
typedef  TYPE_1__ VC_URI_PARTS_T ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_PORT_DELIMITERS ; 
 int /*<<< orphan*/  NETWORK_DELIMITERS ; 
 int /*<<< orphan*/  PATH_DELIMITERS ; 
 int /*<<< orphan*/  QUERY_DELIMITERS ; 
 int /*<<< orphan*/  SCHEME_DELIMITERS ; 
 void* create_unescaped_string (char const*,int) ; 
 int duplicate_string (char const*,void**) ; 
 scalar_t__ isalpha (int) ; 
 int /*<<< orphan*/  parse_authority (TYPE_1__*,char const*,int,char const*) ; 
 int /*<<< orphan*/  parse_query (TYPE_1__*,char const*,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  to_lower_string (void*) ; 
 int /*<<< orphan*/  vc_uri_clear (TYPE_1__*) ; 
 char* vc_uri_find_delimiter (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_uri_set_path_extension (TYPE_1__*) ; 

bool vc_uri_parse( VC_URI_PARTS_T *p_uri, const char *uri )
{
   const char *marker;
   uint32_t len;

   if (!p_uri || !uri)
      return false;

   vc_uri_clear(p_uri);

   /* URI = scheme ":" hier_part [ "?" query ] [ "#" fragment ] */

   /* Find end of scheme, or another separator */
   marker = vc_uri_find_delimiter(uri, SCHEME_DELIMITERS);

   if (*marker == ':')
   {
      len = (marker - uri);
      if (isalpha((int)*uri) && len == 1 && marker[1] == '\\')
      {
         /* Looks like a bare, absolute DOS/Windows filename with a drive letter */
         /* coverity[double_free] Pointer freed and set to NULL */
         bool ret = duplicate_string(uri, &p_uri->path);
         vc_uri_set_path_extension(p_uri);
         return ret;
      }

      p_uri->scheme = create_unescaped_string(uri, len);
      if (!p_uri->scheme)
         goto error;

      to_lower_string(p_uri->scheme);  /* Schemes should be handled case-insensitively */
      uri = marker + 1;
   }

   if (uri[0] == '/' && uri[1] == '/') /* hier-part includes authority */
   {
      const char *userinfo_end = NULL;

      /* authority = [ userinfo "@" ] host [ ":" port ] */
      uri += 2;

      marker = vc_uri_find_delimiter(uri, NETWORK_DELIMITERS);
      if (*marker == '@')
      {
         userinfo_end = marker;
         marker = vc_uri_find_delimiter(marker + 1, HOST_PORT_DELIMITERS);
      }

      if (!parse_authority(p_uri, uri, marker - uri, userinfo_end))
         goto error;
      uri = marker;
   }

   /* path */
   marker = vc_uri_find_delimiter(uri, PATH_DELIMITERS);
   len = marker - uri;
   if (len)
   {
      p_uri->path = create_unescaped_string(uri, len);
      vc_uri_set_path_extension(p_uri);
      if (!p_uri->path)
         goto error;
   }

   /* query */
   if (*marker == '?')
   {
      uri = marker + 1;
      marker = vc_uri_find_delimiter(uri, QUERY_DELIMITERS);
      if (!parse_query(p_uri, uri, marker - uri))
         goto error;
   }

   /* fragment */
   if (*marker == '#')
   {
      uri = marker + 1;
      p_uri->fragment = create_unescaped_string(uri, strlen(uri));
      if (!p_uri->fragment)
         goto error;
   }

   return true;

error:
   vc_uri_clear(p_uri);
   return false;
}