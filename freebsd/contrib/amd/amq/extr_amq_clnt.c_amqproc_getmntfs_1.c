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
typedef  int /*<<< orphan*/  voidp ;
typedef  int /*<<< orphan*/  res ;
typedef  int /*<<< orphan*/  amq_mount_info_list ;
typedef  int /*<<< orphan*/  XDRPROC_T_TYPE ;
typedef  int /*<<< orphan*/  SVC_IN_ARG_TYPE ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  AMQPROC_GETMNTFS ; 
 scalar_t__ RPC_SUCCESS ; 
 int /*<<< orphan*/  TIMEOUT ; 
 scalar_t__ clnt_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xdr_amq_mount_info_list ; 
 scalar_t__ xdr_void ; 

amq_mount_info_list *
amqproc_getmntfs_1(voidp argp, CLIENT *clnt)
{
  static amq_mount_info_list res;

  memset((char *) &res, 0, sizeof(res));
  if (clnt_call(clnt, AMQPROC_GETMNTFS, (XDRPROC_T_TYPE) xdr_void, argp,
		(XDRPROC_T_TYPE) xdr_amq_mount_info_list,
		(SVC_IN_ARG_TYPE) &res, TIMEOUT) != RPC_SUCCESS) {
    return (NULL);
  }
  return (&res);
}