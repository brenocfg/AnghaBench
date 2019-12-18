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
struct sockaddr_storage {scalar_t__ ss_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  laddr ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 int recvfrom (int,char*,int,int,struct sockaddr*,int*) ; 
 int sockaddr2ascii (struct sockaddr*,int,struct sockaddr_storage*,int) ; 

int
Curl_os400_recvfrom(int sd, char * buffer, int buflen, int flags,
                                struct sockaddr * fromaddr, int * addrlen)
{
  int rcvlen;
  struct sockaddr_storage laddr;
  int laddrlen = sizeof(laddr);

  if(!fromaddr || !addrlen || *addrlen <= 0)
    return recvfrom(sd, buffer, buflen, flags, fromaddr, addrlen);

  laddr.ss_family = AF_UNSPEC;          /* To detect if unused. */
  rcvlen = recvfrom(sd, buffer, buflen, flags,
                    (struct sockaddr *) &laddr, &laddrlen);

  if(rcvlen < 0)
    return rcvlen;

  if(laddr.ss_family == AF_UNSPEC)
    laddrlen = 0;
  else {
    laddrlen = sockaddr2ascii(fromaddr, *addrlen, &laddr, laddrlen);
    if(laddrlen < 0)
      return laddrlen;
  }
  *addrlen = laddrlen;
  return rcvlen;
}