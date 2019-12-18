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
struct pxa27x_keypad_platform_data {unsigned int direct_key_num; unsigned long debounce_interval; scalar_t__ enable_rotary1; scalar_t__ enable_rotary0; scalar_t__ matrix_key_cols; scalar_t__ matrix_key_rows; } ;
struct pxa27x_keypad {int direct_key_mask; struct pxa27x_keypad_platform_data* pdata; } ;

/* Variables and functions */
 unsigned long DEFAULT_KPREC ; 
 int /*<<< orphan*/  KPC ; 
 unsigned long KPC_ASACT ; 
 unsigned long KPC_DE ; 
 unsigned long KPC_DIE ; 
 unsigned long KPC_DKN (unsigned int) ; 
 unsigned long KPC_ME ; 
 unsigned long KPC_MIE ; 
 unsigned long KPC_MKCN (scalar_t__) ; 
 unsigned long KPC_MKRN (scalar_t__) ; 
 unsigned long KPC_MS_ALL ; 
 unsigned long KPC_REE0 ; 
 unsigned long KPC_REE1 ; 
 unsigned long KPC_RE_ZERO_DEB ; 
 int /*<<< orphan*/  KPKDI ; 
 int /*<<< orphan*/  KPREC ; 
 int /*<<< orphan*/  keypad_writel (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void pxa27x_keypad_config(struct pxa27x_keypad *keypad)
{
	struct pxa27x_keypad_platform_data *pdata = keypad->pdata;
	unsigned int mask = 0, direct_key_num = 0;
	unsigned long kpc = 0;

	/* enable matrix keys with automatic scan */
	if (pdata->matrix_key_rows && pdata->matrix_key_cols) {
		kpc |= KPC_ASACT | KPC_MIE | KPC_ME | KPC_MS_ALL;
		kpc |= KPC_MKRN(pdata->matrix_key_rows) |
		       KPC_MKCN(pdata->matrix_key_cols);
	}

	/* enable rotary key, debounce interval same as direct keys */
	if (pdata->enable_rotary0) {
		mask |= 0x03;
		direct_key_num = 2;
		kpc |= KPC_REE0;
	}

	if (pdata->enable_rotary1) {
		mask |= 0x0c;
		direct_key_num = 4;
		kpc |= KPC_REE1;
	}

	if (pdata->direct_key_num > direct_key_num)
		direct_key_num = pdata->direct_key_num;

	keypad->direct_key_mask = ((2 << direct_key_num) - 1) & ~mask;

	/* enable direct key */
	if (direct_key_num)
		kpc |= KPC_DE | KPC_DIE | KPC_DKN(direct_key_num);

	keypad_writel(KPC, kpc | KPC_RE_ZERO_DEB);
	keypad_writel(KPREC, DEFAULT_KPREC);
	keypad_writel(KPKDI, pdata->debounce_interval);
}