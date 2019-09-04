#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  user_passwd; } ;
struct connectdata {int /*<<< orphan*/  passwd; int /*<<< orphan*/  user; TYPE_1__ bits; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  IMAP_LOGIN ; 
 int /*<<< orphan*/  IMAP_STOP ; 
 int /*<<< orphan*/  free (char*) ; 
 char* imap_atom (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  imap_sendf (struct connectdata*,char*,char*,char*) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode imap_perform_login(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  char *user;
  char *passwd;

  /* Check we have a username and password to authenticate with and end the
     connect phase if we don't */
  if(!conn->bits.user_passwd) {
    state(conn, IMAP_STOP);

    return result;
  }

  /* Make sure the username and password are in the correct atom format */
  user = imap_atom(conn->user, false);
  passwd = imap_atom(conn->passwd, false);

  /* Send the LOGIN command */
  result = imap_sendf(conn, "LOGIN %s %s", user ? user : "",
                      passwd ? passwd : "");

  free(user);
  free(passwd);

  if(!result)
    state(conn, IMAP_LOGIN);

  return result;
}