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
typedef  int /*<<< orphan*/  u32 ;
struct svc_rqst {int dummy; } ;
struct svc_export {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSID_NUM ; 
 int /*<<< orphan*/  mk_fsid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct svc_export* rqst_exp_find (struct svc_rqst*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct svc_export *find_fsidzero_export(struct svc_rqst *rqstp)
{
	u32 fsidv[2];

	mk_fsid(FSID_NUM, fsidv, 0, 0, 0, NULL);

	return rqst_exp_find(rqstp, FSID_NUM, fsidv);
}