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
typedef  int /*<<< orphan*/  build_id ;

/* Variables and functions */
 int BUILD_ID_SIZE ; 
 int /*<<< orphan*/  build_id__sprintf (int /*<<< orphan*/ *,int,char*) ; 
 int build_id_cache__remove_s (char*,char const*) ; 
 scalar_t__ filename__read_build_id (char const*,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 int /*<<< orphan*/  pr_info (char*,char*,char const*,char*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int build_id_cache__remove_file(const char *filename,
				       const char *debugdir)
{
	u8 build_id[BUILD_ID_SIZE];
	char sbuild_id[BUILD_ID_SIZE * 2 + 1];

	int err;

	if (filename__read_build_id(filename, &build_id, sizeof(build_id)) < 0) {
		pr_debug("Couldn't read a build-id in %s\n", filename);
		return -1;
	}

	build_id__sprintf(build_id, sizeof(build_id), sbuild_id);
	err = build_id_cache__remove_s(sbuild_id, debugdir);
	if (verbose)
		pr_info("Removing %s %s: %s\n", sbuild_id, filename,
			err ? "FAIL" : "Ok");

	return err;
}