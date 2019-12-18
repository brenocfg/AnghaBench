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
typedef  int /*<<< orphan*/  uint8_t ;
struct stat {size_t st_size; } ;
struct carlfw {int dummy; } ;
struct carl9170fw_otus_desc {int /*<<< orphan*/  miniboot_size; int /*<<< orphan*/  feature_set; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CARL9170FW_MINIBOOT ; 
 int /*<<< orphan*/  CARL9170FW_OTUS_DESC_CUR_VER ; 
 scalar_t__ IS_ERR_OR_NULL (char*) ; 
 scalar_t__ OTUS_MAGIC ; 
 scalar_t__ carl9170fw_supports (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct carl9170fw_otus_desc* carlfw_find_desc (struct carlfw*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* carlfw_mod_headroom (struct carlfw*,size_t) ; 
 int /*<<< orphan*/  carlfw_store (struct carlfw*) ; 
 int /*<<< orphan*/  cpu_to_le16 (size_t) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int fread (char*,size_t,int,int /*<<< orphan*/ *) ; 
 int fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int add_mini(struct carlfw *fw, const char *mini)
{
	struct stat file_stat;
	struct carl9170fw_otus_desc *otus_desc = NULL;
	FILE *m = NULL;
	char *buf = NULL;
	size_t extra;
	int err;

	m = fopen(mini, "r");
	if (m == NULL) {
		fprintf(stderr, "Failed to open file %s (%d).\n",
			mini, errno);
		err = -errno;
		goto fail;
	}

	err = fstat(fileno(m), &file_stat);
	if (err) {
		fprintf(stderr, "Failed to query file infos from "
				"\"%s\" (%d).\n", mini, errno);
		err = -errno;
		goto fail;
	}
	extra = file_stat.st_size;

	otus_desc = carlfw_find_desc(fw, (uint8_t *) OTUS_MAGIC,
				     sizeof(*otus_desc),
				     CARL9170FW_OTUS_DESC_CUR_VER);
	if (!otus_desc) {
		fprintf(stderr, "No OTUS descriptor found\n");
		goto fail;
	}

	if (carl9170fw_supports(otus_desc->feature_set, CARL9170FW_MINIBOOT)) {
		fprintf(stderr, "Firmware has already a miniboot image.\n");
		goto fail;
	}

	otus_desc->feature_set |= cpu_to_le32(BIT(CARL9170FW_MINIBOOT));
	otus_desc->miniboot_size = cpu_to_le16(extra);

	buf = carlfw_mod_headroom(fw, extra);
	if (IS_ERR_OR_NULL(buf)) {
		fprintf(stderr, "Unable to add miniboot image.\n");
		goto fail;
	}

	err = fread(buf, extra, 1, m);
	if (err != 1) {
		fprintf(stderr, "Unable to load miniboot.\n");
		goto fail;
	}

	carlfw_store(fw);
	fclose(m);

	return 0;

fail:
	if (m)
		fclose(m);

	return err;
}