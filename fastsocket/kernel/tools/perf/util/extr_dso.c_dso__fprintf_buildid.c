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
struct dso {int /*<<< orphan*/  build_id; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUILD_ID_SIZE ; 
 int /*<<< orphan*/  build_id__sprintf (int /*<<< orphan*/ ,int,char*) ; 
 size_t fprintf (int /*<<< orphan*/ *,char*,char*) ; 

size_t dso__fprintf_buildid(struct dso *dso, FILE *fp)
{
	char sbuild_id[BUILD_ID_SIZE * 2 + 1];

	build_id__sprintf(dso->build_id, sizeof(dso->build_id), sbuild_id);
	return fprintf(fp, "%s", sbuild_id);
}