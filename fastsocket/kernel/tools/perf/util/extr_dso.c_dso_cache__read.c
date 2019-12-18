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
typedef  int u64 ;
struct machine {int dummy; } ;
struct dso_cache {int offset; int size; int /*<<< orphan*/  data; } ;
struct dso {int /*<<< orphan*/  cache; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int DSO__DATA_CACHE_MASK ; 
 scalar_t__ DSO__DATA_CACHE_SIZE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  close (int) ; 
 int dso__data_fd (struct dso*,struct machine*) ; 
 int /*<<< orphan*/  dso_cache__insert (int /*<<< orphan*/ *,struct dso_cache*) ; 
 int dso_cache__memcpy (struct dso_cache*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (struct dso_cache*) ; 
 int lseek (int,int,int /*<<< orphan*/ ) ; 
 int read (int,int /*<<< orphan*/ ,scalar_t__) ; 
 struct dso_cache* zalloc (scalar_t__) ; 

__attribute__((used)) static ssize_t
dso_cache__read(struct dso *dso, struct machine *machine,
		 u64 offset, u8 *data, ssize_t size)
{
	struct dso_cache *cache;
	ssize_t ret;
	int fd;

	fd = dso__data_fd(dso, machine);
	if (fd < 0)
		return -1;

	do {
		u64 cache_offset;

		ret = -ENOMEM;

		cache = zalloc(sizeof(*cache) + DSO__DATA_CACHE_SIZE);
		if (!cache)
			break;

		cache_offset = offset & DSO__DATA_CACHE_MASK;
		ret = -EINVAL;

		if (-1 == lseek(fd, cache_offset, SEEK_SET))
			break;

		ret = read(fd, cache->data, DSO__DATA_CACHE_SIZE);
		if (ret <= 0)
			break;

		cache->offset = cache_offset;
		cache->size   = ret;
		dso_cache__insert(&dso->cache, cache);

		ret = dso_cache__memcpy(cache, offset, data, size);

	} while (0);

	if (ret <= 0)
		free(cache);

	close(fd);
	return ret;
}