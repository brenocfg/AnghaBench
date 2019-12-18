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
struct connectdata {int dummy; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int FALSE ; 
 scalar_t__ pop3_parse_custom_request (struct connectdata*) ; 
 scalar_t__ pop3_parse_url_path (struct connectdata*) ; 
 scalar_t__ pop3_regular_transfer (struct connectdata*,int*) ; 

__attribute__((used)) static CURLcode pop3_do(struct connectdata *conn, bool *done)
{
  CURLcode result = CURLE_OK;

  *done = FALSE; /* default to false */

  /* Parse the URL path */
  result = pop3_parse_url_path(conn);
  if(result)
    return result;

  /* Parse the custom request */
  result = pop3_parse_custom_request(conn);
  if(result)
    return result;

  result = pop3_regular_transfer(conn, done);

  return result;
}