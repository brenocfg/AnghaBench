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
typedef  int /*<<< orphan*/  amq_setopt ;
typedef  int /*<<< orphan*/  XDRPROC_T_TYPE ;
typedef  int /*<<< orphan*/  SVC_IN_ARG_TYPE ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  AMQPROC_SETOPT ; 
 scalar_t__ RPC_SUCCESS ; 
 int /*<<< orphan*/  TIMEOUT ; 
 scalar_t__ clnt_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xdr_amq_setopt ; 
 scalar_t__ xdr_int ; 

int *
amqproc_setopt_1(amq_setopt *argp, CLIENT *clnt)
{
  static int res;

  memset((char *) &res, 0, sizeof(res));
  if (clnt_call(clnt, AMQPROC_SETOPT, (XDRPROC_T_TYPE) xdr_amq_setopt,
		(SVC_IN_ARG_TYPE) argp, (XDRPROC_T_TYPE) xdr_int,
		(SVC_IN_ARG_TYPE) &res, TIMEOUT) != RPC_SUCCESS) {
    return (NULL);
  }
  return (&res);
}