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
typedef  scalar_t__ time_t ;
struct TYPE_2__ {scalar_t__ expiry_time; scalar_t__ flags; } ;
struct rsi {TYPE_1__ h; int /*<<< orphan*/  out_token; int /*<<< orphan*/  out_handle; void* minor_status; void* major_status; int /*<<< orphan*/  in_token; int /*<<< orphan*/  in_handle; } ;
struct cache_detail {int dummy; } ;
typedef  int /*<<< orphan*/  rsii ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  cache_put (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ dup_to_netobj (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ get_expiry (char**) ; 
 int /*<<< orphan*/  memset (struct rsi*,int /*<<< orphan*/ ,int) ; 
 int qword_get (char**,char*,int) ; 
 int /*<<< orphan*/  rsi_cache ; 
 int /*<<< orphan*/  rsi_free (struct rsi*) ; 
 struct rsi* rsi_lookup (struct rsi*) ; 
 struct rsi* rsi_update (struct rsi*,struct rsi*) ; 
 void* simple_strtoul (char*,char**,int) ; 

__attribute__((used)) static int rsi_parse(struct cache_detail *cd,
		    char *mesg, int mlen)
{
	/* context token expiry major minor context token */
	char *buf = mesg;
	char *ep;
	int len;
	struct rsi rsii, *rsip = NULL;
	time_t expiry;
	int status = -EINVAL;

	memset(&rsii, 0, sizeof(rsii));
	/* handle */
	len = qword_get(&mesg, buf, mlen);
	if (len < 0)
		goto out;
	status = -ENOMEM;
	if (dup_to_netobj(&rsii.in_handle, buf, len))
		goto out;

	/* token */
	len = qword_get(&mesg, buf, mlen);
	status = -EINVAL;
	if (len < 0)
		goto out;
	status = -ENOMEM;
	if (dup_to_netobj(&rsii.in_token, buf, len))
		goto out;

	rsip = rsi_lookup(&rsii);
	if (!rsip)
		goto out;

	rsii.h.flags = 0;
	/* expiry */
	expiry = get_expiry(&mesg);
	status = -EINVAL;
	if (expiry == 0)
		goto out;

	/* major/minor */
	len = qword_get(&mesg, buf, mlen);
	if (len <= 0)
		goto out;
	rsii.major_status = simple_strtoul(buf, &ep, 10);
	if (*ep)
		goto out;
	len = qword_get(&mesg, buf, mlen);
	if (len <= 0)
		goto out;
	rsii.minor_status = simple_strtoul(buf, &ep, 10);
	if (*ep)
		goto out;

	/* out_handle */
	len = qword_get(&mesg, buf, mlen);
	if (len < 0)
		goto out;
	status = -ENOMEM;
	if (dup_to_netobj(&rsii.out_handle, buf, len))
		goto out;

	/* out_token */
	len = qword_get(&mesg, buf, mlen);
	status = -EINVAL;
	if (len < 0)
		goto out;
	status = -ENOMEM;
	if (dup_to_netobj(&rsii.out_token, buf, len))
		goto out;
	rsii.h.expiry_time = expiry;
	rsip = rsi_update(&rsii, rsip);
	status = 0;
out:
	rsi_free(&rsii);
	if (rsip)
		cache_put(&rsip->h, &rsi_cache);
	else
		status = -ENOMEM;
	return status;
}