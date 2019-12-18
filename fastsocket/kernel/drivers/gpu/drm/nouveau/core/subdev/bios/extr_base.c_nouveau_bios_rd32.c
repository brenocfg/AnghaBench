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
typedef  size_t u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nouveau_object {int dummy; } ;
struct nouveau_bios {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_unaligned_le32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32
nouveau_bios_rd32(struct nouveau_object *object, u64 addr)
{
	struct nouveau_bios *bios = (void *)object;
	return get_unaligned_le32(&bios->data[addr]);
}