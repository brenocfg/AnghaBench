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
typedef  int u32 ;
struct geode_aes_op {scalar_t__ len; scalar_t__ dir; scalar_t__ mode; int flags; int /*<<< orphan*/  iv; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int AES_CTRL_CBC ; 
 int AES_CTRL_DCA ; 
 int AES_CTRL_ENCRYPT ; 
 int AES_CTRL_SCA ; 
 int AES_CTRL_WRKEY ; 
 scalar_t__ AES_DIR_ENCRYPT ; 
 int AES_FLAGS_HIDDENKEY ; 
 scalar_t__ AES_MODE_CBC ; 
 int /*<<< orphan*/  AES_WRITEIV0_REG ; 
 int /*<<< orphan*/  AES_WRITEKEY0_REG ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  _readfield (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _writefield (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int do_crypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int
geode_aes_crypt(struct geode_aes_op *op)
{
	u32 flags = 0;
	unsigned long iflags;
	int ret;

	if (op->len == 0)
		return 0;

	/* If the source and destination is the same, then
	 * we need to turn on the coherent flags, otherwise
	 * we don't need to worry
	 */

	flags |= (AES_CTRL_DCA | AES_CTRL_SCA);

	if (op->dir == AES_DIR_ENCRYPT)
		flags |= AES_CTRL_ENCRYPT;

	/* Start the critical section */

	spin_lock_irqsave(&lock, iflags);

	if (op->mode == AES_MODE_CBC) {
		flags |= AES_CTRL_CBC;
		_writefield(AES_WRITEIV0_REG, op->iv);
	}

	if (!(op->flags & AES_FLAGS_HIDDENKEY)) {
		flags |= AES_CTRL_WRKEY;
		_writefield(AES_WRITEKEY0_REG, op->key);
	}

	ret = do_crypt(op->src, op->dst, op->len, flags);
	BUG_ON(ret);

	if (op->mode == AES_MODE_CBC)
		_readfield(AES_WRITEIV0_REG, op->iv);

	spin_unlock_irqrestore(&lock, iflags);

	return op->len;
}