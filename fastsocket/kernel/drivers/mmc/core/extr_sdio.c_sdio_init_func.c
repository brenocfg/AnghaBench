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
struct sdio_func {unsigned int num; } ;
struct mmc_card {struct sdio_func** sdio_func; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IS_ERR (struct sdio_func*) ; 
 int PTR_ERR (struct sdio_func*) ; 
 unsigned int SDIO_MAX_FUNCS ; 
 struct sdio_func* sdio_alloc_func (struct mmc_card*) ; 
 int sdio_read_fbr (struct sdio_func*) ; 
 int sdio_read_func_cis (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_remove_func (struct sdio_func*) ; 

__attribute__((used)) static int sdio_init_func(struct mmc_card *card, unsigned int fn)
{
	int ret;
	struct sdio_func *func;

	BUG_ON(fn > SDIO_MAX_FUNCS);

	func = sdio_alloc_func(card);
	if (IS_ERR(func))
		return PTR_ERR(func);

	func->num = fn;

	ret = sdio_read_fbr(func);
	if (ret)
		goto fail;

	ret = sdio_read_func_cis(func);
	if (ret)
		goto fail;

	card->sdio_func[fn - 1] = func;

	return 0;

fail:
	/*
	 * It is okay to remove the function here even though we hold
	 * the host lock as we haven't registered the device yet.
	 */
	sdio_remove_func(func);
	return ret;
}