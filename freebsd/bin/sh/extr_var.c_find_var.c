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
struct var {int name_len; int /*<<< orphan*/  text; struct var* next; } ;

/* Variables and functions */
 unsigned int VTABSIZE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char const*,int) ; 
 struct var** vartab ; 

__attribute__((used)) static struct var *
find_var(const char *name, struct var ***vppp, int *lenp)
{
	unsigned int hashval;
	int len;
	struct var *vp, **vpp;
	const char *p = name;

	hashval = 0;
	while (*p && *p != '=')
		hashval = 2 * hashval + (unsigned char)*p++;
	len = p - name;

	if (lenp)
		*lenp = len;
	vpp = &vartab[hashval % VTABSIZE];
	if (vppp)
		*vppp = vpp;

	for (vp = *vpp ; vp ; vpp = &vp->next, vp = *vpp) {
		if (vp->name_len != len)
			continue;
		if (memcmp(vp->text, name, len) != 0)
			continue;
		if (vppp)
			*vppp = vpp;
		return vp;
	}
	return NULL;
}