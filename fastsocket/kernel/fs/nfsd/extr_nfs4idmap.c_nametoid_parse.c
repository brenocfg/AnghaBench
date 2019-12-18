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
struct TYPE_2__ {scalar_t__ expiry_time; int /*<<< orphan*/  flags; } ;
struct ent {TYPE_1__ h; int /*<<< orphan*/  id; int /*<<< orphan*/  name; int /*<<< orphan*/  type; int /*<<< orphan*/  authname; } ;
struct cache_detail {int dummy; } ;
typedef  int /*<<< orphan*/  ent ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_NEGATIVE ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IDMAP_NAMESZ ; 
 int /*<<< orphan*/  IDMAP_TYPE_GROUP ; 
 int /*<<< orphan*/  IDMAP_TYPE_USER ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  cache_put (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ get_expiry (char**) ; 
 int get_int (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct ent*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nametoid_cache ; 
 struct ent* nametoid_lookup (struct ent*) ; 
 struct ent* nametoid_update (struct ent*,struct ent*) ; 
 int qword_get (char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
nametoid_parse(struct cache_detail *cd, char *buf, int buflen)
{
	struct ent ent, *res;
	char *buf1;
	int error = -EINVAL;

	if (buf[buflen - 1] != '\n')
		return (-EINVAL);
	buf[buflen - 1]= '\0';

	buf1 = kmalloc(PAGE_SIZE, GFP_KERNEL);
	if (buf1 == NULL)
		return (-ENOMEM);

	memset(&ent, 0, sizeof(ent));

	/* Authentication name */
	if (qword_get(&buf, buf1, PAGE_SIZE) <= 0)
		goto out;
	memcpy(ent.authname, buf1, sizeof(ent.authname));

	/* Type */
	if (qword_get(&buf, buf1, PAGE_SIZE) <= 0)
		goto out;
	ent.type = strcmp(buf1, "user") == 0 ?
		IDMAP_TYPE_USER : IDMAP_TYPE_GROUP;

	/* Name */
	error = qword_get(&buf, buf1, PAGE_SIZE);
	if (error <= 0 || error >= IDMAP_NAMESZ)
		goto out;
	memcpy(ent.name, buf1, sizeof(ent.name));

	/* expiry */
	ent.h.expiry_time = get_expiry(&buf);
	if (ent.h.expiry_time == 0)
		goto out;

	/* ID */
	error = get_int(&buf, &ent.id);
	if (error == -EINVAL)
		goto out;
	if (error == -ENOENT)
		set_bit(CACHE_NEGATIVE, &ent.h.flags);

	error = -ENOMEM;
	res = nametoid_lookup(&ent);
	if (res == NULL)
		goto out;
	res = nametoid_update(&ent, res);
	if (res == NULL)
		goto out;

	cache_put(&res->h, &nametoid_cache);
	error = 0;
out:
	kfree(buf1);

	return (error);
}