#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* dentry; } ;
struct TYPE_5__ {scalar_t__ expiry_time; int /*<<< orphan*/  flags; } ;
struct svc_export {char* ex_pathname; int ex_flags; int ex_anon_uid; int ex_anon_gid; int ex_fsid; char* ex_uuid; TYPE_3__ ex_path; int /*<<< orphan*/  ex_fslocs; TYPE_1__ h; struct auth_domain* ex_client; } ;
struct cache_detail {int dummy; } ;
struct auth_domain {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_NEGATIVE ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct auth_domain* auth_domain_find (char*) ; 
 int /*<<< orphan*/  auth_domain_put (struct auth_domain*) ; 
 int /*<<< orphan*/  cache_flush () ; 
 int check_export (int /*<<< orphan*/ ,int*,char*) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  exp_put (struct svc_export*) ; 
 int fsloc_parse (char**,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ get_expiry (char**) ; 
 int get_int (char**,int*) ; 
 int kern_path (char*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* kmemdup (char*,int,int /*<<< orphan*/ ) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd4_fslocs_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_put (TYPE_3__*) ; 
 int qword_get (char**,char*,int /*<<< orphan*/ ) ; 
 int secinfo_parse (char**,char*,struct svc_export*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 struct svc_export* svc_export_lookup (struct svc_export*) ; 
 struct svc_export* svc_export_update (struct svc_export*,struct svc_export*) ; 

__attribute__((used)) static int svc_export_parse(struct cache_detail *cd, char *mesg, int mlen)
{
	/* client path expiry [flags anonuid anongid fsid] */
	char *buf;
	int len;
	int err;
	struct auth_domain *dom = NULL;
	struct svc_export exp = {}, *expp;
	int an_int;

	if (mesg[mlen-1] != '\n')
		return -EINVAL;
	mesg[mlen-1] = 0;
	dprintk("svc_export_parse: '%s'\n", mesg);

	buf = kmalloc(PAGE_SIZE, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	/* client */
	err = -EINVAL;
	len = qword_get(&mesg, buf, PAGE_SIZE);
	if (len <= 0)
		goto out;

	err = -ENOENT;
	dom = auth_domain_find(buf);
	if (!dom)
		goto out;

	/* path */
	err = -EINVAL;
	if ((len = qword_get(&mesg, buf, PAGE_SIZE)) <= 0)
		goto out1;

	err = kern_path(buf, 0, &exp.ex_path);
	if (err)
		goto out1;

	exp.ex_client = dom;

	err = -ENOMEM;
	exp.ex_pathname = kstrdup(buf, GFP_KERNEL);
	if (!exp.ex_pathname)
		goto out2;

	/* expiry */
	err = -EINVAL;
	exp.h.expiry_time = get_expiry(&mesg);
	if (exp.h.expiry_time == 0)
		goto out3;

	/* flags */
	err = get_int(&mesg, &an_int);
	if (err == -ENOENT) {
		err = 0;
		set_bit(CACHE_NEGATIVE, &exp.h.flags);
	} else {
		if (err || an_int < 0)
			goto out3;
		exp.ex_flags= an_int;
	
		/* anon uid */
		err = get_int(&mesg, &an_int);
		if (err)
			goto out3;
		exp.ex_anon_uid= an_int;

		/* anon gid */
		err = get_int(&mesg, &an_int);
		if (err)
			goto out3;
		exp.ex_anon_gid= an_int;

		/* fsid */
		err = get_int(&mesg, &an_int);
		if (err)
			goto out3;
		exp.ex_fsid = an_int;

		while ((len = qword_get(&mesg, buf, PAGE_SIZE)) > 0) {
			if (strcmp(buf, "fsloc") == 0)
				err = fsloc_parse(&mesg, buf, &exp.ex_fslocs);
			else if (strcmp(buf, "uuid") == 0) {
				/* expect a 16 byte uuid encoded as \xXXXX... */
				len = qword_get(&mesg, buf, PAGE_SIZE);
				if (len != 16)
					err  = -EINVAL;
				else {
					exp.ex_uuid =
						kmemdup(buf, 16, GFP_KERNEL);
					if (exp.ex_uuid == NULL)
						err = -ENOMEM;
				}
			} else if (strcmp(buf, "secinfo") == 0)
				err = secinfo_parse(&mesg, buf, &exp);
			else
				/* quietly ignore unknown words and anything
				 * following. Newer user-space can try to set
				 * new values, then see what the result was.
				 */
				break;
			if (err)
				goto out4;
		}

		err = check_export(exp.ex_path.dentry->d_inode, &exp.ex_flags,
				   exp.ex_uuid);
		if (err)
			goto out4;
	}

	expp = svc_export_lookup(&exp);
	if (expp)
		expp = svc_export_update(&exp, expp);
	else
		err = -ENOMEM;
	cache_flush();
	if (expp == NULL)
		err = -ENOMEM;
	else
		exp_put(expp);
out4:
	nfsd4_fslocs_free(&exp.ex_fslocs);
	kfree(exp.ex_uuid);
out3:
	kfree(exp.ex_pathname);
out2:
	path_put(&exp.ex_path);
out1:
	auth_domain_put(dom);
out:
	kfree(buf);
	if (err)
		dprintk("svc_export_parse: err %d\n", err);
	return err;
}