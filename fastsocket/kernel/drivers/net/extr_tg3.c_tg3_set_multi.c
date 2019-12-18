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
struct tg3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_HASH_REG_0 ; 
 int /*<<< orphan*/  MAC_HASH_REG_1 ; 
 int /*<<< orphan*/  MAC_HASH_REG_2 ; 
 int /*<<< orphan*/  MAC_HASH_REG_3 ; 
 int /*<<< orphan*/  tw32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tg3_set_multi(struct tg3 *tp, unsigned int accept_all)
{
	/* accept or reject all multicast frames */
	tw32(MAC_HASH_REG_0, accept_all ? 0xffffffff : 0);
	tw32(MAC_HASH_REG_1, accept_all ? 0xffffffff : 0);
	tw32(MAC_HASH_REG_2, accept_all ? 0xffffffff : 0);
	tw32(MAC_HASH_REG_3, accept_all ? 0xffffffff : 0);
}