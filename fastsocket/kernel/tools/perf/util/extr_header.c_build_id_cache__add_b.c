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

/* Variables and functions */
 int BUILD_ID_SIZE ; 
 int /*<<< orphan*/  build_id__sprintf (int /*<<< orphan*/  const*,size_t,char*) ; 
 int build_id_cache__add_s (char*,char const*,char const*,int,int) ; 

__attribute__((used)) static int build_id_cache__add_b(const u8 *build_id, size_t build_id_size,
				 const char *name, const char *debugdir,
				 bool is_kallsyms, bool is_vdso)
{
	char sbuild_id[BUILD_ID_SIZE * 2 + 1];

	build_id__sprintf(build_id, build_id_size, sbuild_id);

	return build_id_cache__add_s(sbuild_id, debugdir, name,
				     is_kallsyms, is_vdso);
}