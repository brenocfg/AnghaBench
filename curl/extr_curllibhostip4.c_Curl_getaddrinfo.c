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
struct connectdata {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  Curl_addrinfo ;

/* Variables and functions */
 int /*<<< orphan*/ * Curl_ipv4_resolve_r (char const*,int) ; 
 int /*<<< orphan*/  infof (int /*<<< orphan*/ ,char*,char const*) ; 

Curl_addrinfo *Curl_getaddrinfo(struct connectdata *conn,
                                const char *hostname,
                                int port,
                                int *waitp)
{
  Curl_addrinfo *ai = NULL;

#ifdef CURL_DISABLE_VERBOSE_STRINGS
  (void)conn;
#endif

  *waitp = 0; /* synchronous response only */

  ai = Curl_ipv4_resolve_r(hostname, port);
  if(!ai)
    infof(conn->data, "Curl_ipv4_resolve_r failed for %s\n", hostname);

  return ai;
}