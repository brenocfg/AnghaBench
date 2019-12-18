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
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;

/* Variables and functions */
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  VX_BOOT_FILE_INQ ; 
 int net_clnt_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  xdr_void ; 
 int /*<<< orphan*/  xdr_wrapstring ; 

__attribute__((used)) static int
net_get_boot_file (char **pBootFile)
{
  enum clnt_stat status;

  status = net_clnt_call (VX_BOOT_FILE_INQ, xdr_void, (char *) 0,
			  xdr_wrapstring, pBootFile);
  return (status == RPC_SUCCESS) ? 0 : -1;
}