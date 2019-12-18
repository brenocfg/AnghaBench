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
struct nouveau_bios {int size; int* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nv_info (struct nouveau_bios*,char*) ; 
 scalar_t__ nvbios_checksum (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static int
nouveau_bios_score(struct nouveau_bios *bios, const bool writeable)
{
	if (bios->size < 3 || !bios->data || bios->data[0] != 0x55 ||
			bios->data[1] != 0xAA) {
		nv_info(bios, "... signature not found\n");
		return 0;
	}

	if (nvbios_checksum(bios->data,
			min_t(u32, bios->data[2] * 512, bios->size))) {
		nv_info(bios, "... checksum invalid\n");
		/* if a ro image is somewhat bad, it's probably all rubbish */
		return writeable ? 2 : 1;
	}

	nv_info(bios, "... appears to be valid\n");
	return 3;
}