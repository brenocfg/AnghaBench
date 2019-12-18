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
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  IMAP_LOGOUT ; 
 int /*<<< orphan*/  imap_sendf (struct connectdata*,char*) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode imap_perform_logout(struct connectdata *conn)
{
  /* Send the LOGOUT command */
  CURLcode result = imap_sendf(conn, "LOGOUT");

  if(!result)
    state(conn, IMAP_LOGOUT);

  return result;
}