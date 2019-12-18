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
struct ldtabl {int dummy; } ;
typedef  int /*<<< orphan*/  ldtabl ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;

/* Variables and functions */
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  VX_STATE_INQ ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int net_clnt_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_ldtabl ; 
 int /*<<< orphan*/  xdr_void ; 

__attribute__((used)) static int
net_get_symbols (ldtabl *pLoadTable)
{
  enum clnt_stat status;

  memset ((char *) pLoadTable, '\0', sizeof (struct ldtabl));

  status = net_clnt_call (VX_STATE_INQ, xdr_void, 0, xdr_ldtabl, pLoadTable);
  return (status == RPC_SUCCESS) ? 0 : -1;
}