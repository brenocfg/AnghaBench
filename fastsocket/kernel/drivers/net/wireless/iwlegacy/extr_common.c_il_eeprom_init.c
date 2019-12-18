#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct il_priv {TYPE_2__* ops; scalar_t__ eeprom; TYPE_1__* cfg; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_4__ {int (* eeprom_acquire_semaphore ) (struct il_priv*) ;int /*<<< orphan*/  (* eeprom_release_semaphore ) (struct il_priv*) ;int /*<<< orphan*/  (* apm_init ) (struct il_priv*) ;} ;
struct TYPE_3__ {int eeprom_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_EEPROM_GP ; 
 int /*<<< orphan*/  CSR_EEPROM_REG ; 
 int CSR_EEPROM_REG_MSK_ADDR ; 
 int /*<<< orphan*/  CSR_EEPROM_REG_READ_VALID_MSK ; 
 int /*<<< orphan*/  D_EEPROM (char*,...) ; 
 int /*<<< orphan*/  EEPROM_VERSION ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IL_EEPROM_ACCESS_TIMEOUT ; 
 int /*<<< orphan*/  IL_ERR (char*,...) ; 
 int _il_poll_bit (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _il_rd (struct il_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _il_wr (struct il_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  il_apm_stop (struct il_priv*) ; 
 int /*<<< orphan*/  il_eeprom_free (struct il_priv*) ; 
 int /*<<< orphan*/  il_eeprom_query16 (struct il_priv*,int /*<<< orphan*/ ) ; 
 int il_eeprom_verify_signature (struct il_priv*) ; 
 scalar_t__ kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct il_priv*) ; 
 int stub2 (struct il_priv*) ; 
 int /*<<< orphan*/  stub3 (struct il_priv*) ; 

int
il_eeprom_init(struct il_priv *il)
{
	__le16 *e;
	u32 gp = _il_rd(il, CSR_EEPROM_GP);
	int sz;
	int ret;
	u16 addr;

	/* allocate eeprom */
	sz = il->cfg->eeprom_size;
	D_EEPROM("NVM size = %d\n", sz);
	il->eeprom = kzalloc(sz, GFP_KERNEL);
	if (!il->eeprom) {
		ret = -ENOMEM;
		goto alloc_err;
	}
	e = (__le16 *) il->eeprom;

	il->ops->apm_init(il);

	ret = il_eeprom_verify_signature(il);
	if (ret < 0) {
		IL_ERR("EEPROM not found, EEPROM_GP=0x%08x\n", gp);
		ret = -ENOENT;
		goto err;
	}

	/* Make sure driver (instead of uCode) is allowed to read EEPROM */
	ret = il->ops->eeprom_acquire_semaphore(il);
	if (ret < 0) {
		IL_ERR("Failed to acquire EEPROM semaphore.\n");
		ret = -ENOENT;
		goto err;
	}

	/* eeprom is an array of 16bit values */
	for (addr = 0; addr < sz; addr += sizeof(u16)) {
		u32 r;

		_il_wr(il, CSR_EEPROM_REG,
		       CSR_EEPROM_REG_MSK_ADDR & (addr << 1));

		ret =
		    _il_poll_bit(il, CSR_EEPROM_REG,
				 CSR_EEPROM_REG_READ_VALID_MSK,
				 CSR_EEPROM_REG_READ_VALID_MSK,
				 IL_EEPROM_ACCESS_TIMEOUT);
		if (ret < 0) {
			IL_ERR("Time out reading EEPROM[%d]\n", addr);
			goto done;
		}
		r = _il_rd(il, CSR_EEPROM_REG);
		e[addr / 2] = cpu_to_le16(r >> 16);
	}

	D_EEPROM("NVM Type: %s, version: 0x%x\n", "EEPROM",
		 il_eeprom_query16(il, EEPROM_VERSION));

	ret = 0;
done:
	il->ops->eeprom_release_semaphore(il);

err:
	if (ret)
		il_eeprom_free(il);
	/* Reset chip to save power until we load uCode during "up". */
	il_apm_stop(il);
alloc_err:
	return ret;
}