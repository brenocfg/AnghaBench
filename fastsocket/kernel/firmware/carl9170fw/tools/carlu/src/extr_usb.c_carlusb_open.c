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
struct carlu {int dummy; } ;

/* Variables and functions */
 struct carlu* ERR_PTR (int) ; 
 struct carlu* carlu_alloc_driver (int) ; 
 int /*<<< orphan*/  carlusb_free_driver (struct carlu*) ; 
 int carlusb_get_dev (struct carlu*,int) ; 
 int carlusb_init (struct carlu*) ; 

__attribute__((used)) static struct carlu *carlusb_open(void)
{
	struct carlu *tmp;
	int err;

	tmp = carlu_alloc_driver(sizeof(*tmp));
	if (tmp == NULL)
		return NULL;

	err = carlusb_init(tmp);
	if (err < 0)
		goto err_out;

	err = carlusb_get_dev(tmp, true);
	if (err < 0)
		goto err_out;

	return tmp;

err_out:
	carlusb_free_driver(tmp);
	return ERR_PTR(err);
}