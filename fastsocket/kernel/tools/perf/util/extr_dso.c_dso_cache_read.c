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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct machine {int dummy; } ;
struct dso_cache {int dummy; } ;
struct dso {int /*<<< orphan*/  cache; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct dso_cache* dso_cache__find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dso_cache__memcpy (struct dso_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dso_cache__read (struct dso*,struct machine*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t dso_cache_read(struct dso *dso, struct machine *machine,
			      u64 offset, u8 *data, ssize_t size)
{
	struct dso_cache *cache;

	cache = dso_cache__find(&dso->cache, offset);
	if (cache)
		return dso_cache__memcpy(cache, offset, data, size);
	else
		return dso_cache__read(dso, machine, offset, data, size);
}