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
struct sockaddr {int dummy; } ;
typedef  scalar_t__ curl_socklen_t ;

/* Variables and functions */
 int EAI_MEMORY ; 
 int QadrtConvertE2A (char*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getnameinfo (struct sockaddr const*,scalar_t__,char*,scalar_t__,char*,scalar_t__,int) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int
Curl_getnameinfo_a(const struct sockaddr * sa, curl_socklen_t salen,
              char * nodename, curl_socklen_t nodenamelen,
              char * servname, curl_socklen_t servnamelen,
              int flags)

{
  char *enodename = NULL;
  char *eservname = NULL;
  int status;

  if(nodename && nodenamelen) {
    enodename = malloc(nodenamelen);
    if(!enodename)
      return EAI_MEMORY;
  }

  if(servname && servnamelen) {
    eservname = malloc(servnamelen);
    if(!eservname) {
      free(enodename);
      return EAI_MEMORY;
    }
  }

  status = getnameinfo(sa, salen, enodename, nodenamelen,
                       eservname, servnamelen, flags);

  if(!status) {
    int i;
    if(enodename) {
      i = QadrtConvertE2A(nodename, enodename,
        nodenamelen - 1, strlen(enodename));
      nodename[i] = '\0';
      }

    if(eservname) {
      i = QadrtConvertE2A(servname, eservname,
        servnamelen - 1, strlen(eservname));
      servname[i] = '\0';
      }
    }

  free(enodename);
  free(eservname);
  return status;
}