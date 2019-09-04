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
struct connectdata {int /*<<< orphan*/  tls_upgraded; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ pop3_init (struct connectdata*) ; 

__attribute__((used)) static CURLcode pop3_setup_connection(struct connectdata *conn)
{
  /* Initialise the POP3 layer */
  CURLcode result = pop3_init(conn);
  if(result)
    return result;

  /* Clear the TLS upgraded flag */
  conn->tls_upgraded = FALSE;

  return CURLE_OK;
}