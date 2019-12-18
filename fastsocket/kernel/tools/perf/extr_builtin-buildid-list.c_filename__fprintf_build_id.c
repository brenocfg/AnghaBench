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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUILD_ID_SIZE ; 
 int /*<<< orphan*/  build_id__sprintf (int /*<<< orphan*/ *,int,char*) ; 
 int filename__read_build_id (char const*,int /*<<< orphan*/ *,int) ; 
 int fprintf (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int filename__fprintf_build_id(const char *name, FILE *fp)
{
	u8 build_id[BUILD_ID_SIZE];
	char sbuild_id[BUILD_ID_SIZE * 2 + 1];

	if (filename__read_build_id(name, build_id,
				    sizeof(build_id)) != sizeof(build_id))
		return 0;

	build_id__sprintf(build_id, sizeof(build_id), sbuild_id);
	return fprintf(fp, "%s\n", sbuild_id);
}