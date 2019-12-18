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
struct dso {int /*<<< orphan*/  build_id; int /*<<< orphan*/  has_build_id; } ;

/* Variables and functions */
 int BUILD_ID_SIZE ; 
 scalar_t__ asprintf (char**,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  build_id__sprintf (int /*<<< orphan*/ ,int,char*) ; 
 char* buildid_dir ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char*,char*) ; 

char *dso__build_id_filename(struct dso *self, char *bf, size_t size)
{
	char build_id_hex[BUILD_ID_SIZE * 2 + 1];

	if (!self->has_build_id)
		return NULL;

	build_id__sprintf(self->build_id, sizeof(self->build_id), build_id_hex);
	if (bf == NULL) {
		if (asprintf(&bf, "%s/.build-id/%.2s/%s", buildid_dir,
			     build_id_hex, build_id_hex + 2) < 0)
			return NULL;
	} else
		snprintf(bf, size, "%s/.build-id/%.2s/%s", buildid_dir,
			 build_id_hex, build_id_hex + 2);
	return bf;
}