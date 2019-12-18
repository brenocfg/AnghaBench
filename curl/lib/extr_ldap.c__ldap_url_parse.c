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
typedef  int /*<<< orphan*/  LDAPURLDesc ;

/* Variables and functions */
 int LDAP_NO_MEMORY ; 
 int LDAP_SUCCESS ; 
 int /*<<< orphan*/  _ldap_free_urldesc (int /*<<< orphan*/ *) ; 
 int _ldap_url_parse2 (struct connectdata const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * calloc (int,int) ; 

__attribute__((used)) static int _ldap_url_parse(const struct connectdata *conn,
                           LDAPURLDesc **ludpp)
{
  LDAPURLDesc *ludp = calloc(1, sizeof(*ludp));
  int rc;

  *ludpp = NULL;
  if(!ludp)
     return LDAP_NO_MEMORY;

  rc = _ldap_url_parse2(conn, ludp);
  if(rc != LDAP_SUCCESS) {
    _ldap_free_urldesc(ludp);
    ludp = NULL;
  }
  *ludpp = ludp;
  return (rc);
}