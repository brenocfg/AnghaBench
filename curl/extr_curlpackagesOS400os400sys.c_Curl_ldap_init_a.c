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
 int /*<<< orphan*/  QadrtConvertA2E (char*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ ldap_init (char*,int) ; 
 char* malloc (unsigned int) ; 
 unsigned int strlen (char*) ; 

void *
Curl_ldap_init_a(char * host, int port)

{
  unsigned int i;
  char * ehost;
  void * result;

  if(!host)
    return (void *) ldap_init(host, port);

  i = strlen(host);

  ehost = malloc(i + 1);
  if(!ehost)
    return (void *) NULL;

  QadrtConvertA2E(ehost, host, i, i);
  ehost[i] = '\0';
  result = (void *) ldap_init(ehost, port);
  free(ehost);
  return result;
}