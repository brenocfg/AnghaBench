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

/* Variables and functions */
 int LDAP_NO_MEMORY ; 
 int /*<<< orphan*/  QadrtConvertA2E (char*,char*,int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int ldap_simple_bind_s (void*,char*,char*) ; 
 char* malloc (int) ; 
 int strlen (char*) ; 

int
Curl_ldap_simple_bind_s_a(void * ld, char * dn, char * passwd)

{
  int i;
  char * edn;
  char * epasswd;

  edn = (char *) NULL;
  epasswd = (char *) NULL;

  if(dn) {
    i = strlen(dn);

    edn = malloc(i + 1);
    if(!edn)
      return LDAP_NO_MEMORY;

    QadrtConvertA2E(edn, dn, i, i);
    edn[i] = '\0';
  }

  if(passwd) {
    i = strlen(passwd);

    epasswd = malloc(i + 1);
    if(!epasswd) {
      free(edn);
      return LDAP_NO_MEMORY;
    }

    QadrtConvertA2E(epasswd, passwd, i, i);
    epasswd[i] = '\0';
  }

  i = ldap_simple_bind_s(ld, edn, epasswd);
  free(epasswd);
  free(edn);
  return i;
}