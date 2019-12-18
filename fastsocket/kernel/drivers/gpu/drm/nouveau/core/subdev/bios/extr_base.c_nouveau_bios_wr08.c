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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u64 ;
struct nouveau_object {int dummy; } ;
struct nouveau_bios {int /*<<< orphan*/ * data; } ;

/* Variables and functions */

__attribute__((used)) static void
nouveau_bios_wr08(struct nouveau_object *object, u64 addr, u8 data)
{
	struct nouveau_bios *bios = (void *)object;
	bios->data[addr] = data;
}