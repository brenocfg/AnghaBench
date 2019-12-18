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
struct idmap_hashtable {int dummy; } ;
struct idmap_hashent {size_t ih_namelen; int /*<<< orphan*/  ih_expires; int /*<<< orphan*/  ih_name; } ;

/* Variables and functions */
 struct idmap_hashent* idmap_name_hash (struct idmap_hashtable*,char const*,size_t) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char const*,size_t) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct idmap_hashent *
idmap_lookup_name(struct idmap_hashtable *h, const char *name, size_t len)
{
	struct idmap_hashent *he = idmap_name_hash(h, name, len);

	if (he == NULL)
		return NULL;
	if (he->ih_namelen != len || memcmp(he->ih_name, name, len) != 0)
		return NULL;
	if (time_after(jiffies, he->ih_expires))
		return NULL;
	return he;
}