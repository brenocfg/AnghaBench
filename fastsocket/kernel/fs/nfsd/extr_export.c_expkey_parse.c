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
struct TYPE_2__ {scalar_t__ expiry_time; scalar_t__ flags; } ;
struct svc_expkey {int ek_fsidtype; TYPE_1__ h; int /*<<< orphan*/  ek_path; int /*<<< orphan*/  ek_fsid; struct auth_domain* ek_client; } ;
struct cache_detail {int dummy; } ;
struct auth_domain {int dummy; } ;

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
 int /*<<< orphan*/  cache_put (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 scalar_t__ get_expiry (char**) ; 
 int kern_path (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int key_len (int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  path_put (int /*<<< orphan*/ *) ; 
 int qword_get (char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int simple_strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  svc_expkey_cache ; 
 struct svc_expkey* svc_expkey_lookup (struct svc_expkey*) ; 
 struct svc_expkey* svc_expkey_update (struct svc_expkey*,struct svc_expkey*) ; 

__attribute__((used)) static int expkey_parse(struct cache_detail *cd, char *mesg, int mlen)
{
	/* client fsidtype fsid [path] */
	char *buf;
	int len;
	struct auth_domain *dom = NULL;
	int err;
	int fsidtype;
	char *ep;
	struct svc_expkey key;
	struct svc_expkey *ek = NULL;

	if (mesg[mlen-1] != '\n')
		return -EINVAL;
	mesg[mlen-1] = 0;
	dprintk("expkey_parse: '%s'\n", mesg);

	buf = kmalloc(PAGE_SIZE, GFP_KERNEL);
	err = -ENOMEM;
	if (!buf)
		goto out;

	err = -EINVAL;
	if ((len=qword_get(&mesg, buf, PAGE_SIZE)) <= 0)
		goto out;

	err = -ENOENT;
	dom = auth_domain_find(buf);
	if (!dom)
		goto out;
	dprintk("found domain %s\n", buf);

	err = -EINVAL;
	if ((len=qword_get(&mesg, buf, PAGE_SIZE)) <= 0)
		goto out;
	fsidtype = simple_strtoul(buf, &ep, 10);
	if (*ep)
		goto out;
	dprintk("found fsidtype %d\n", fsidtype);
	if (key_len(fsidtype)==0) /* invalid type */
		goto out;
	if ((len=qword_get(&mesg, buf, PAGE_SIZE)) <= 0)
		goto out;
	dprintk("found fsid length %d\n", len);
	if (len != key_len(fsidtype))
		goto out;

	/* OK, we seem to have a valid key */
	key.h.flags = 0;
	key.h.expiry_time = get_expiry(&mesg);
	if (key.h.expiry_time == 0)
		goto out;

	key.ek_client = dom;	
	key.ek_fsidtype = fsidtype;
	memcpy(key.ek_fsid, buf, len);

	ek = svc_expkey_lookup(&key);
	err = -ENOMEM;
	if (!ek)
		goto out;

	/* now we want a pathname, or empty meaning NEGATIVE  */
	err = -EINVAL;
	len = qword_get(&mesg, buf, PAGE_SIZE);
	if (len < 0)
		goto out;
	dprintk("Path seems to be <%s>\n", buf);
	err = 0;
	if (len == 0) {
		set_bit(CACHE_NEGATIVE, &key.h.flags);
		ek = svc_expkey_update(&key, ek);
		if (!ek)
			err = -ENOMEM;
	} else {
		err = kern_path(buf, 0, &key.ek_path);
		if (err)
			goto out;

		dprintk("Found the path %s\n", buf);

		ek = svc_expkey_update(&key, ek);
		if (!ek)
			err = -ENOMEM;
		path_put(&key.ek_path);
	}
	cache_flush();
 out:
	if (ek)
		cache_put(&ek->h, &svc_expkey_cache);
	if (dom)
		auth_domain_put(dom);
	kfree(buf);
	if (err)
		dprintk("expkey_parse: err %d\n", err);
	return err;
}