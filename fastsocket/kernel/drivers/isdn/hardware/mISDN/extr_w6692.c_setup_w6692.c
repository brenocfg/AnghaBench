#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct w6692_hw {int /*<<< orphan*/  name; scalar_t__ addr; TYPE_1__* bc; } ;
struct TYPE_2__ {scalar_t__ addr; } ;

/* Variables and functions */
 int DEBUG_HW ; 
 int EIO ; 
 int /*<<< orphan*/  ReadW6692 (struct w6692_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  W6692Version (struct w6692_hw*) ; 
 int /*<<< orphan*/  W_D_EXIM ; 
 int /*<<< orphan*/  W_D_EXIR ; 
 int /*<<< orphan*/  W_D_RSTA ; 
 int /*<<< orphan*/  W_IMASK ; 
 int /*<<< orphan*/  W_ISTA ; 
 int debug ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_region (scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
setup_w6692(struct w6692_hw *card)
{
	u32	val;

	if (!request_region(card->addr, 256, card->name)) {
		pr_info("%s: config port %x-%x already in use\n", card->name,
		       card->addr, card->addr + 255);
		return -EIO;
	}
	W6692Version(card);
	card->bc[0].addr = card->addr;
	card->bc[1].addr = card->addr + 0x40;
	val = ReadW6692(card, W_ISTA);
	if (debug & DEBUG_HW)
		pr_notice("%s ISTA=%02x\n", card->name, val);
	val = ReadW6692(card, W_IMASK);
	if (debug & DEBUG_HW)
		pr_notice("%s IMASK=%02x\n", card->name, val);
	val = ReadW6692(card, W_D_EXIR);
	if (debug & DEBUG_HW)
		pr_notice("%s D_EXIR=%02x\n", card->name, val);
	val = ReadW6692(card, W_D_EXIM);
	if (debug & DEBUG_HW)
		pr_notice("%s D_EXIM=%02x\n", card->name, val);
	val = ReadW6692(card, W_D_RSTA);
	if (debug & DEBUG_HW)
		pr_notice("%s D_RSTA=%02x\n", card->name, val);
	return 0;
}