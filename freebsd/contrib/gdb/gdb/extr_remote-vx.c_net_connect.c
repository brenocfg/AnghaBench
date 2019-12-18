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
struct TYPE_2__ {unsigned long s_addr; } ;
struct sockaddr_in {scalar_t__ sin_port; int /*<<< orphan*/  sin_family; TYPE_1__ sin_addr; } ;
struct hostent {scalar_t__ h_addr; } ;
typedef  int /*<<< orphan*/  destAddr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  RDBPROG ; 
 int /*<<< orphan*/  RDBVERS ; 
 int /*<<< orphan*/  RPC_ANYSOCK ; 
 int /*<<< orphan*/  clnt_pcreateerror (char*) ; 
 int /*<<< orphan*/ * clnttcp_create (struct sockaddr_in*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ gethostbyname (char*) ; 
 unsigned long inet_addr (char*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,char,int) ; 
 int /*<<< orphan*/ * pClient ; 
 int /*<<< orphan*/  ptraceSock ; 

__attribute__((used)) static void
net_connect (char *host)
{
  struct sockaddr_in destAddr;
  struct hostent *destHost;
  unsigned long addr;

  /* Get the internet address for the given host.  Allow a numeric
     IP address or a hostname.  */

  addr = inet_addr (host);
  if (addr == -1)
    {
      destHost = (struct hostent *) gethostbyname (host);
      if (destHost == NULL)
	/* FIXME: Probably should include hostname here in quotes.
	   For example if the user types "target vxworks vx960 " it should
	   say "Invalid host `vx960 '." not just "Invalid hostname".  */
	error ("Invalid hostname.  Couldn't find remote host address.");
      addr = *(unsigned long *) destHost->h_addr;
    }

  memset (&destAddr, '\0', sizeof (destAddr));

  destAddr.sin_addr.s_addr = addr;
  destAddr.sin_family = AF_INET;
  destAddr.sin_port = 0;	/* set to actual port that remote
				   ptrace is listening on.  */

  /* Create a tcp client transport on which to issue
     calls to the remote ptrace server.  */

  ptraceSock = RPC_ANYSOCK;
  pClient = clnttcp_create (&destAddr, RDBPROG, RDBVERS, &ptraceSock, 0, 0);
  /* FIXME, here is where we deal with different version numbers of the
     proto */

  if (pClient == NULL)
    {
      clnt_pcreateerror ("\tnet_connect");
      error ("Couldn't connect to remote target.");
    }
}