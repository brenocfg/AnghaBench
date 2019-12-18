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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct map {int /*<<< orphan*/  type; int /*<<< orphan*/  unmap_ip; int /*<<< orphan*/  map_ip; } ;
struct list_head {int dummy; } ;
struct dso {int dummy; } ;
typedef  int /*<<< orphan*/  newfilename ;
typedef  enum map_type { ____Placeholder_map_type } map_type ;

/* Variables and functions */
 int PATH_MAX ; 
 struct dso* __dsos__findnew (struct list_head*,char*) ; 
 int /*<<< orphan*/  dso__set_loaded (struct dso*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct map*) ; 
 int /*<<< orphan*/  identity__map_ip ; 
 int is_anon_memory (char*) ; 
 int is_no_dso_memory (char*) ; 
 int is_vdso_map (char*) ; 
 struct map* malloc (int) ; 
 int /*<<< orphan*/  map__init (struct map*,int,scalar_t__,scalar_t__,scalar_t__,struct dso*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 struct dso* vdso__dso_findnew (struct list_head*) ; 

struct map *map__new(struct list_head *dsos__list, u64 start, u64 len,
		     u64 pgoff, u32 pid, char *filename,
		     enum map_type type)
{
	struct map *self = malloc(sizeof(*self));

	if (self != NULL) {
		char newfilename[PATH_MAX];
		struct dso *dso;
		int anon, no_dso, vdso;

		anon = is_anon_memory(filename);
		vdso = is_vdso_map(filename);
		no_dso = is_no_dso_memory(filename);

		if (anon) {
			snprintf(newfilename, sizeof(newfilename), "/tmp/perf-%d.map", pid);
			filename = newfilename;
		}

		if (vdso) {
			pgoff = 0;
			dso = vdso__dso_findnew(dsos__list);
		} else
			dso = __dsos__findnew(dsos__list, filename);

		if (dso == NULL)
			goto out_delete;

		map__init(self, type, start, start + len, pgoff, dso);

		if (anon || no_dso) {
			self->map_ip = self->unmap_ip = identity__map_ip;

			/*
			 * Set memory without DSO as loaded. All map__find_*
			 * functions still return NULL, and we avoid the
			 * unnecessary map__load warning.
			 */
			if (no_dso)
				dso__set_loaded(dso, self->type);
		}
	}
	return self;
out_delete:
	free(self);
	return NULL;
}