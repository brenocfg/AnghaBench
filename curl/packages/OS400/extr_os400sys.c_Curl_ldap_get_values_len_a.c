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
struct berval {int dummy; } ;
typedef  int /*<<< orphan*/  LDAPMessage ;

/* Variables and functions */
 int /*<<< orphan*/  LDAP_NO_MEMORY ; 
 int /*<<< orphan*/  QadrtConvertA2E (char*,char const*,int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ldap_err2string (int /*<<< orphan*/ ) ; 
 struct berval** ldap_get_values_len (void*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ldap_set_lderrno (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* malloc (int) ; 
 int strlen (char const*) ; 

struct berval * *
Curl_ldap_get_values_len_a(void * ld, LDAPMessage * entry, const char * attr)

{
  char * cp;
  struct berval * * result;

  cp = (char *) NULL;

  if(attr) {
    int i = strlen(attr);

    cp = malloc(i + 1);
    if(!cp) {
      ldap_set_lderrno(ld, LDAP_NO_MEMORY, NULL,
                       ldap_err2string(LDAP_NO_MEMORY));
      return (struct berval * *) NULL;
    }

    QadrtConvertA2E(cp, attr, i, i);
    cp[i] = '\0';
  }

  result = ldap_get_values_len(ld, entry, cp);
  free(cp);

  /* Result data are binary in nature, so they haven't been
     converted to EBCDIC. Therefore do not convert. */

  return result;
}