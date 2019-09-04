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
struct connectdata {int /*<<< orphan*/  (* do_it ) (struct connectdata*,int*) ;struct connectdata* handler; } ;
struct Curl_easy {struct connectdata* conn; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  DEBUGASSERT (struct connectdata*) ; 
 int /*<<< orphan*/  do_complete (struct connectdata*) ; 
 int /*<<< orphan*/  stub1 (struct connectdata*,int*) ; 

__attribute__((used)) static CURLcode multi_do(struct Curl_easy *data, bool *done)
{
  CURLcode result = CURLE_OK;
  struct connectdata *conn = data->conn;

  DEBUGASSERT(conn);
  DEBUGASSERT(conn->handler);

  if(conn->handler->do_it) {
    /* generic protocol-specific function pointer set in curl_connect() */
    result = conn->handler->do_it(conn, done);

    if(!result && *done)
      /* do_complete must be called after the protocol-specific DO function */
      do_complete(conn);
  }
  return result;
}