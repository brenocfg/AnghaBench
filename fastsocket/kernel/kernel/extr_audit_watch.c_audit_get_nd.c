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
struct nameidata {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LOOKUP_PARENT ; 
 int /*<<< orphan*/  kfree (struct nameidata*) ; 
 struct nameidata* kmalloc (int,int /*<<< orphan*/ ) ; 
 int path_lookup (char*,int /*<<< orphan*/ ,struct nameidata*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int audit_get_nd(char *path, struct nameidata **ndp, struct nameidata **ndw)
{
	struct nameidata *ndparent, *ndwatch;
	int err;

	ndparent = kmalloc(sizeof(*ndparent), GFP_KERNEL);
	if (unlikely(!ndparent))
		return -ENOMEM;

	ndwatch = kmalloc(sizeof(*ndwatch), GFP_KERNEL);
	if (unlikely(!ndwatch)) {
		kfree(ndparent);
		return -ENOMEM;
	}

	err = path_lookup(path, LOOKUP_PARENT, ndparent);
	if (err) {
		kfree(ndparent);
		kfree(ndwatch);
		return err;
	}

	err = path_lookup(path, 0, ndwatch);
	if (err) {
		kfree(ndwatch);
		ndwatch = NULL;
	}

	*ndp = ndparent;
	*ndw = ndwatch;

	return 0;
}