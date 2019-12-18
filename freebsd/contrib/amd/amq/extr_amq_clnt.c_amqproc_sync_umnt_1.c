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
typedef  int /*<<< orphan*/  res ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
typedef  int /*<<< orphan*/  amq_sync_umnt ;
typedef  int /*<<< orphan*/  amq_string ;
typedef  int /*<<< orphan*/  XDRPROC_T_TYPE ;
typedef  int /*<<< orphan*/  SVC_IN_ARG_TYPE ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  AMQPROC_SYNC_UMNT ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  TIMEOUT ; 
 int clnt_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xdr_amq_string ; 
 scalar_t__ xdr_amq_sync_umnt ; 

amq_sync_umnt *
amqproc_sync_umnt_1(amq_string *argp, CLIENT *clnt)
{
  static amq_sync_umnt res;
  enum clnt_stat rv;

  memset((char *) &res, 0, sizeof(res));
  if ((rv = clnt_call(clnt, AMQPROC_SYNC_UMNT,
		(XDRPROC_T_TYPE) xdr_amq_string, (SVC_IN_ARG_TYPE) argp,
		(XDRPROC_T_TYPE) xdr_amq_sync_umnt, (SVC_IN_ARG_TYPE) &res,
		TIMEOUT)) != RPC_SUCCESS) {
    return (NULL);
  }
  return &res;
}