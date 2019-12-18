#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {void* sin6_port; void* sin6_family; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {void* sin_port; void* sin_family; int /*<<< orphan*/  sin_addr; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
struct hostent {char** h_addr_list; scalar_t__ h_addrtype; int /*<<< orphan*/ * h_name; } ;
typedef  scalar_t__ curl_socklen_t ;
struct TYPE_6__ {scalar_t__ ai_family; void* ai_addr; scalar_t__ ai_addrlen; int /*<<< orphan*/  ai_socktype; struct TYPE_6__* ai_next; struct TYPE_6__* ai_canonname; } ;
typedef  TYPE_1__ Curl_addrinfo ;
typedef  scalar_t__ CURLcode ;
typedef  void* CURL_SA_FAMILY_T ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  Curl_freeaddrinfo (TYPE_1__*) ; 
 int /*<<< orphan*/  DEBUGASSERT (int) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 void* calloc (int,size_t) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 void* htons (unsigned short) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_1__* strdup (int /*<<< orphan*/ *) ; 

Curl_addrinfo *
Curl_he2ai(const struct hostent *he, int port)
{
  Curl_addrinfo *ai;
  Curl_addrinfo *prevai = NULL;
  Curl_addrinfo *firstai = NULL;
  struct sockaddr_in *addr;
#ifdef ENABLE_IPV6
  struct sockaddr_in6 *addr6;
#endif
  CURLcode result = CURLE_OK;
  int i;
  char *curr;

  if(!he)
    /* no input == no output! */
    return NULL;

  DEBUGASSERT((he->h_name != NULL) && (he->h_addr_list != NULL));

  for(i = 0; (curr = he->h_addr_list[i]) != NULL; i++) {

    size_t ss_size;
#ifdef ENABLE_IPV6
    if(he->h_addrtype == AF_INET6)
      ss_size = sizeof(struct sockaddr_in6);
    else
#endif
      ss_size = sizeof(struct sockaddr_in);

    ai = calloc(1, sizeof(Curl_addrinfo));
    if(!ai) {
      result = CURLE_OUT_OF_MEMORY;
      break;
    }
    ai->ai_canonname = strdup(he->h_name);
    if(!ai->ai_canonname) {
      result = CURLE_OUT_OF_MEMORY;
      free(ai);
      break;
    }
    ai->ai_addr = calloc(1, ss_size);
    if(!ai->ai_addr) {
      result = CURLE_OUT_OF_MEMORY;
      free(ai->ai_canonname);
      free(ai);
      break;
    }

    if(!firstai)
      /* store the pointer we want to return from this function */
      firstai = ai;

    if(prevai)
      /* make the previous entry point to this */
      prevai->ai_next = ai;

    ai->ai_family = he->h_addrtype;

    /* we return all names as STREAM, so when using this address for TFTP
       the type must be ignored and conn->socktype be used instead! */
    ai->ai_socktype = SOCK_STREAM;

    ai->ai_addrlen = (curl_socklen_t)ss_size;

    /* leave the rest of the struct filled with zero */

    switch(ai->ai_family) {
    case AF_INET:
      addr = (void *)ai->ai_addr; /* storage area for this info */

      memcpy(&addr->sin_addr, curr, sizeof(struct in_addr));
      addr->sin_family = (CURL_SA_FAMILY_T)(he->h_addrtype);
      addr->sin_port = htons((unsigned short)port);
      break;

#ifdef ENABLE_IPV6
    case AF_INET6:
      addr6 = (void *)ai->ai_addr; /* storage area for this info */

      memcpy(&addr6->sin6_addr, curr, sizeof(struct in6_addr));
      addr6->sin6_family = (CURL_SA_FAMILY_T)(he->h_addrtype);
      addr6->sin6_port = htons((unsigned short)port);
      break;
#endif
    }

    prevai = ai;
  }

  if(result) {
    Curl_freeaddrinfo(firstai);
    firstai = NULL;
  }

  return firstai;
}