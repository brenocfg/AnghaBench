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
typedef  int /*<<< orphan*/  u8 ;
struct vblk_disk {int /*<<< orphan*/  disk_id; } ;
struct TYPE_2__ {struct vblk_disk disk; } ;
struct vblk {TYPE_1__ vblk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GUID_SIZE ; 
 scalar_t__ VBLK_SIZE_DSK4 ; 
 int get_unaligned_be32 (int /*<<< orphan*/  const*) ; 
 int ldm_relative (int /*<<< orphan*/  const*,int,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ldm_parse_dsk4 (const u8 *buffer, int buflen, struct vblk *vb)
{
	int r_objid, r_name, len;
	struct vblk_disk *disk;

	BUG_ON (!buffer || !vb);

	r_objid = ldm_relative (buffer, buflen, 0x18, 0);
	r_name  = ldm_relative (buffer, buflen, 0x18, r_objid);
	len     = r_name;
	if (len < 0)
		return false;

	len += VBLK_SIZE_DSK4;
	if (len != get_unaligned_be32(buffer + 0x14))
		return false;

	disk = &vb->vblk.disk;
	memcpy (disk->disk_id, buffer + 0x18 + r_name, GUID_SIZE);
	return true;
}