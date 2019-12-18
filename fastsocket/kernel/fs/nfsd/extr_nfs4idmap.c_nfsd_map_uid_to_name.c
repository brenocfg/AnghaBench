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
struct svc_rqst {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  IDMAP_TYPE_USER ; 
 int do_id_to_name (struct svc_rqst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int
nfsd_map_uid_to_name(struct svc_rqst *rqstp, __u32 id, char *name)
{
	return do_id_to_name(rqstp, IDMAP_TYPE_USER, id, name);
}