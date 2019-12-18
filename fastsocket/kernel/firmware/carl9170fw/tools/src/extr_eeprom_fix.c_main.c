#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct carlfw {int dummy; } ;
struct carl9170fw_fix_desc {int dummy; } ;
struct TYPE_3__ {char option; int argc; int (* func ) (struct carlfw*,struct carl9170fw_fix_desc*,char,int,char**) ;} ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  CARL9170FW_FIX_DESC_CUR_VER ; 
 int EINVAL ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 scalar_t__ FIX_MAGIC ; 
 scalar_t__ IS_ERR_OR_NULL (struct carlfw*) ; 
 int PTR_ERR (struct carlfw*) ; 
 struct carl9170fw_fix_desc* carlfw_find_desc (struct carlfw*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct carlfw* carlfw_load (char*) ; 
 int /*<<< orphan*/  carlfw_release (struct carlfw*) ; 
 int carlfw_store (struct carlfw*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* programm_function ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int stub1 (struct carlfw*,struct carl9170fw_fix_desc*,char,int,char**) ; 
 int /*<<< orphan*/  user_education () ; 

int main(int argc, char *args[])
{
	struct carl9170fw_fix_desc *fix;
	struct carlfw *fw = NULL;
	unsigned int i;
	int err = 0;
	char option;

	if (argc < 3 || argc > 6) {
		err = -EINVAL;
		goto out;
	}

	fw = carlfw_load(args[1]);
	if (IS_ERR_OR_NULL(fw)) {
		err = PTR_ERR(fw);
		fprintf(stderr, "Failed to open file \"%s\" (%d).\n",
			args[1], err);
		goto out;
	}

	fix = carlfw_find_desc(fw, (uint8_t *)FIX_MAGIC, sizeof(*fix),
			       CARL9170FW_FIX_DESC_CUR_VER);

	option = args[2][0];
	for (i = 0; i < ARRAY_SIZE(programm_function); i++) {
		if (programm_function[i].option != option)
			continue;

		if (argc != programm_function[i].argc) {
			err = -EINVAL;
			goto out;
		}

		err = programm_function[i].func(fw, fix, option, argc, args);
		if (err)
			goto out;

		break;
	}
	if (i == ARRAY_SIZE(programm_function)) {
		fprintf(stderr, "Unknown option: '%c'\n",
			args[2][0]);
		goto out;
	}

	err = carlfw_store(fw);
	if (err) {
		fprintf(stderr, "Failed to apply changes (%d).\n", err);
		goto out;
	}

out:
	carlfw_release(fw);

	if (err) {
		if (err == -EINVAL)
			user_education();
		else
			fprintf(stderr, "%s\n", strerror(err));
	}

	return err ? EXIT_FAILURE : EXIT_SUCCESS;
}