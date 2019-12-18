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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct ldfile {scalar_t__* name; int /*<<< orphan*/  bss_addr; int /*<<< orphan*/  data_addr; int /*<<< orphan*/  txt_addr; } ;
typedef  int /*<<< orphan*/  ldstruct ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  VX_LOAD ; 
 int clnt_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ ,struct ldfile*,struct timeval) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  pClient ; 
 int /*<<< orphan*/  xdr_ldfile ; 
 int /*<<< orphan*/  xdr_wrapstring ; 

__attribute__((used)) static int
net_load (char *filename, CORE_ADDR *pTextAddr, CORE_ADDR *pDataAddr,
	  CORE_ADDR *pBssAddr)
{
  enum clnt_stat status;
  struct ldfile ldstruct;
  struct timeval load_timeout;

  memset ((char *) &ldstruct, '\0', sizeof (ldstruct));

  /* We invoke clnt_call () here directly, instead of through
     net_clnt_call (), because we need to set a large timeout value.
     The load on the target side can take quite a while, easily
     more than 10 seconds.  The user can kill this call by typing
     CTRL-C if there really is a problem with the load.  

     Do not change the tv_sec value without checking -- select() imposes
     a limit of 10**8 on it for no good reason that I can see...  */

  load_timeout.tv_sec = 99999999;	/* A large number, effectively inf. */
  load_timeout.tv_usec = 0;

  status = clnt_call (pClient, VX_LOAD, xdr_wrapstring, &filename, xdr_ldfile,
		      &ldstruct, load_timeout);

  if (status == RPC_SUCCESS)
    {
      if (*ldstruct.name == 0)	/* load failed on VxWorks side */
	return -1;
      *pTextAddr = ldstruct.txt_addr;
      *pDataAddr = ldstruct.data_addr;
      *pBssAddr = ldstruct.bss_addr;
      return 0;
    }
  else
    return -1;
}