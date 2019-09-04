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
typedef  int /*<<< orphan*/  LDAPMessage ;
typedef  int /*<<< orphan*/  BerElement ;

/* Variables and functions */
 int /*<<< orphan*/  QadrtConvertE2A (char*,char*,int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* ldap_next_attribute (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

char *
Curl_ldap_next_attribute_a(void * ld,
                           LDAPMessage * entry, BerElement * berptr)

{
  int i;
  char * cp;
  char * cp2;

  cp = ldap_next_attribute(ld, entry, berptr);

  if(!cp)
    return cp;

  i = strlen(cp);

  cp2 = malloc(i + 1);
  if(!cp2)
    return cp2;

  QadrtConvertE2A(cp2, cp, i, i);
  cp2[i] = '\0';

  /* No way to allocate a buffer here, because it will be released by
     ldap_memfree() and ldap_memalloc() does not exist. The solution is to
     overwrite the EBCDIC buffer with ASCII to return it. */

  strcpy(cp, cp2);
  free(cp2);
  return cp;
}