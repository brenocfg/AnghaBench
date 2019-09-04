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
struct addrinfo {int dummy; } ;

/* Variables and functions */
 int EAI_MEMORY ; 
 int QadrtConvertA2E (char*,char const*,int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getaddrinfo (char*,char*,struct addrinfo const*,struct addrinfo**) ; 
 char* malloc (int) ; 
 int strlen (char const*) ; 

int
Curl_getaddrinfo_a(const char * nodename, const char * servname,
            const struct addrinfo * hints,
            struct addrinfo * * res)

{
  char * enodename;
  char * eservname;
  int status;
  int i;

  enodename = (char *) NULL;
  eservname = (char *) NULL;

  if(nodename) {
    i = strlen(nodename);

    enodename = malloc(i + 1);
    if(!enodename)
      return EAI_MEMORY;

    i = QadrtConvertA2E(enodename, nodename, i, i);
    enodename[i] = '\0';
  }

  if(servname) {
    i = strlen(servname);

    eservname = malloc(i + 1);
    if(!eservname) {
      free(enodename);
      return EAI_MEMORY;
    }

    QadrtConvertA2E(eservname, servname, i, i);
    eservname[i] = '\0';
  }

  status = getaddrinfo(enodename, eservname, hints, res);
  free(enodename);
  free(eservname);
  return status;
}