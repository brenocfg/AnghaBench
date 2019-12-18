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
typedef  int /*<<< orphan*/  uint8_t ;
struct http_t {int dummy; } ;
struct http_connection_t {int dummy; } ;
typedef  scalar_t__ retro_time_t ;

/* Variables and functions */
 int NET_HTTP_GET_CONNECT_ERROR ; 
 int NET_HTTP_GET_MALFORMED_URL ; 
 int NET_HTTP_GET_OK ; 
 int NET_HTTP_GET_TIMEOUT ; 
 scalar_t__ cpu_features_get_time_usec () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  net_http_connection_done (struct http_connection_t*) ; 
 int /*<<< orphan*/  net_http_connection_free (struct http_connection_t*) ; 
 int /*<<< orphan*/  net_http_connection_iterate (struct http_connection_t*) ; 
 struct http_connection_t* net_http_connection_new (char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * net_http_data (struct http_t*,size_t*,int) ; 
 int /*<<< orphan*/  net_http_delete (struct http_t*) ; 
 struct http_t* net_http_new (struct http_connection_t*) ; 
 int /*<<< orphan*/  net_http_update (struct http_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int net_http_get(const char **result, size_t *size, const char *url, retro_time_t *timeout)
{
   size_t length;
   uint8_t* data                  = NULL;
   char* res                      = NULL;
   int ret                        = NET_HTTP_GET_OK;
   struct http_t* http            = NULL;
   retro_time_t t0                = cpu_features_get_time_usec();
   struct http_connection_t *conn = net_http_connection_new(url, "GET", NULL);

   *result = NULL;

   /* Error creating the connection descriptor. */
   if (!conn)
      goto error;

   /* Don't bother with timeouts here, it's just a string scan. */
   while (!net_http_connection_iterate(conn)) {}

   /* Error finishing the connection descriptor. */
   if (!net_http_connection_done(conn))
   {
      ret = NET_HTTP_GET_MALFORMED_URL;
      goto error;
   }

   http = net_http_new(conn);

   /* Error connecting to the endpoint. */
   if (!http)
   {
      ret = NET_HTTP_GET_CONNECT_ERROR;
      goto error;
   }

   while (!net_http_update(http, NULL, NULL))
   {
      /* Timeout error. */
      if (timeout && (cpu_features_get_time_usec() - t0) > *timeout)
      {
         ret = NET_HTTP_GET_TIMEOUT;
         goto error;
      }
   }

   data = net_http_data(http, &length, false);

   if (data)
   {
      res = (char*)malloc(length + 1);

      /* Allocation error. */
      if (!res)
         goto error;

      memcpy((void*)res, (void*)data, length);
      free(data);
      res[length] = 0;
      *result = res;
   }
   else
   {
      length = 0;
      *result = NULL;
   }

   if (size)
      *size = length;

error:
   if (http)
      net_http_delete(http);

   if (conn)
      net_http_connection_free(conn);

   if (timeout)
   {
      t0 = cpu_features_get_time_usec() - t0;

      if (t0 < *timeout)
         *timeout -= t0;
      else
         *timeout = 0;
   }

   return ret;
}