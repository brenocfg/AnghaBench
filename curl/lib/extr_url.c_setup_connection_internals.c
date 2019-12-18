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
struct connectdata {int /*<<< orphan*/  port; struct Curl_handler* handler; } ;
struct Curl_handler {int /*<<< orphan*/  defport; scalar_t__ (* setup_connection ) (struct connectdata*) ;} ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ stub1 (struct connectdata*) ; 

__attribute__((used)) static CURLcode setup_connection_internals(struct connectdata *conn)
{
  const struct Curl_handler * p;
  CURLcode result;

  /* Perform setup complement if some. */
  p = conn->handler;

  if(p->setup_connection) {
    result = (*p->setup_connection)(conn);

    if(result)
      return result;

    p = conn->handler;              /* May have changed. */
  }

  if(conn->port < 0)
    /* we check for -1 here since if proxy was detected already, this
       was very likely already set to the proxy port */
    conn->port = p->defport;

  return CURLE_OK;
}