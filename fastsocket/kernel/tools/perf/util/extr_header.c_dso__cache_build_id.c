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
struct dso {char* long_name; int /*<<< orphan*/  build_id; int /*<<< orphan*/  short_name; scalar_t__ kernel; } ;

/* Variables and functions */
 int build_id_cache__add_b (int /*<<< orphan*/ ,int,char*,char const*,int,int) ; 
 int is_vdso_map (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dso__cache_build_id(struct dso *dso, const char *debugdir)
{
	bool is_kallsyms = dso->kernel && dso->long_name[0] != '/';
	bool is_vdso = is_vdso_map(dso->short_name);

	return build_id_cache__add_b(dso->build_id, sizeof(dso->build_id),
				     dso->long_name, debugdir,
				     is_kallsyms, is_vdso);
}