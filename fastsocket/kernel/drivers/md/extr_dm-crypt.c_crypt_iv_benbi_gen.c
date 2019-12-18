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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct TYPE_3__ {int shift; } ;
struct TYPE_4__ {TYPE_1__ benbi; } ;
struct crypt_config {int iv_size; TYPE_2__ iv_gen_private; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int crypt_iv_benbi_gen(struct crypt_config *cc, u8 *iv, sector_t sector)
{
	__be64 val;

	memset(iv, 0, cc->iv_size - sizeof(u64)); /* rest is cleared below */

	val = cpu_to_be64(((u64)sector << cc->iv_gen_private.benbi.shift) + 1);
	put_unaligned(val, (__be64 *)(iv + cc->iv_size - sizeof(u64)));

	return 0;
}