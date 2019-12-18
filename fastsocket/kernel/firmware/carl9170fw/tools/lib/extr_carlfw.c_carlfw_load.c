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
struct carlfw_file {unsigned long len; int /*<<< orphan*/ * data; scalar_t__ name; } ;
struct carlfw {struct carlfw_file fw; struct carlfw_file hdr; int /*<<< orphan*/  desc_list; } ;
struct carl9170fw_otus_desc {int dummy; } ;
struct carl9170fw_last_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170FW_LAST_DESC_CUR_VER ; 
 int /*<<< orphan*/  CARL9170FW_OTUS_DESC_CUR_VER ; 
 int ENODATA ; 
 int ENOMEM ; 
 struct carlfw* ERR_PTR (int) ; 
 scalar_t__ LAST_MAGIC ; 
 scalar_t__ OTUS_MAGIC ; 
 void* __carlfw_find_desc (struct carlfw_file*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int __carlfw_load (struct carlfw_file*,char const*,char*) ; 
 struct carlfw* calloc (int,int) ; 
 int carlfw_check_crc32s (struct carlfw*) ; 
 int carlfw_parse_descs (struct carlfw*,struct carl9170fw_otus_desc*) ; 
 int /*<<< orphan*/  carlfw_release (struct carlfw*) ; 
 int /*<<< orphan*/  init_list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,unsigned long) ; 

struct carlfw *carlfw_load(const char *basename)
{
	char filename[256];
	struct carlfw *fw;
	struct carl9170fw_otus_desc *otus_desc;
	struct carl9170fw_last_desc *last_desc;
	struct carlfw_file *hdr_file;
	unsigned long fin, diff, off, rem;
	int err;

	fw = calloc(1, sizeof(*fw));
	if (!fw)
		return ERR_PTR(-ENOMEM);

	init_list_head(&fw->desc_list);

	err = __carlfw_load(&fw->fw, basename, "r");
	if (err)
		goto err_out;

	if (fw->hdr.name)
		hdr_file = &fw->hdr;
	else
		hdr_file = &fw->fw;

	otus_desc = __carlfw_find_desc(hdr_file, (uint8_t *) OTUS_MAGIC,
				       sizeof(*otus_desc),
				       CARL9170FW_OTUS_DESC_CUR_VER);
	last_desc = __carlfw_find_desc(hdr_file, (uint8_t *) LAST_MAGIC,
				       sizeof(*last_desc),
				       CARL9170FW_LAST_DESC_CUR_VER);

	if (!otus_desc || !last_desc ||
	    (unsigned long) otus_desc > (unsigned long) last_desc) {
		err = -ENODATA;
		goto err_out;
	}

	err = carlfw_parse_descs(fw, otus_desc);
	if (err)
		goto err_out;

	fin = (unsigned long)last_desc + sizeof(*last_desc);
	diff = fin - (unsigned long)otus_desc;
	rem = hdr_file->len - (fin - (unsigned long) hdr_file->data);

	if (rem) {
		off = (unsigned long)otus_desc - (unsigned long)hdr_file->data;
		memmove(&hdr_file->data[off],
			((uint8_t *)last_desc) + sizeof(*last_desc), rem);
	}

	hdr_file->len -= diff;
	hdr_file->data = realloc(hdr_file->data, hdr_file->len);
	if (!hdr_file->data && hdr_file->len) {
		err = -ENOMEM;
		goto err_out;
	}

	err = carlfw_check_crc32s(fw);
	if (err && err != -ENODATA)
		goto err_out;

	return fw;

err_out:
	carlfw_release(fw);
	return ERR_PTR(err);
}