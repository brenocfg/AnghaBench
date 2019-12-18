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
struct carlfw {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct carlfw*) ; 
 int PTR_ERR (struct carlfw*) ; 
 int add_mini (struct carlfw*,char*) ; 
 struct carlfw* carlfw_load (char*) ; 
 int /*<<< orphan*/  carlfw_release (struct carlfw*) ; 
 int del_mini (struct carlfw*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mini_help () ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char *args[])
{
	struct carlfw *fw = NULL;
	int err;

	if (argc < 3 || argc > 4) {
		err = -EINVAL;
		goto err_param;
	}

	switch (args[1][0]) {
	case 'a':
		if (argc != 4)
			goto err_param;

		fw = carlfw_load(args[2]);
		if (IS_ERR_OR_NULL(fw)) {
			err = PTR_ERR(fw);
			goto err_out;
		}

		err = add_mini(fw, args[3]);
		break;
	case 'd':
		if (argc != 3)
			goto err_param;

		fw = carlfw_load(args[2]);
		if (IS_ERR_OR_NULL(fw)) {
			err = PTR_ERR(fw);
			goto err_out;
		}

		err = del_mini(fw);
		break;

	default:
		goto err_param;
		break;
	}

	carlfw_release(fw);
	return EXIT_SUCCESS;

err_out:
	carlfw_release(fw);
	fprintf(stderr, "miniboot action failed (%d).\n", err);
	return EXIT_FAILURE;

err_param:
	carlfw_release(fw);
	mini_help();
	return EXIT_FAILURE;
}