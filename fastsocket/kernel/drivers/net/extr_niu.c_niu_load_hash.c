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
typedef  int /*<<< orphan*/  u16 ;
struct niu {int flags; } ;

/* Variables and functions */
 int NIU_FLAGS_XMAC ; 
 int /*<<< orphan*/  niu_load_hash_bmac (struct niu*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  niu_load_hash_xmac (struct niu*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void niu_load_hash(struct niu *np, u16 *hash)
{
	if (np->flags & NIU_FLAGS_XMAC)
		niu_load_hash_xmac(np, hash);
	else
		niu_load_hash_bmac(np, hash);
}