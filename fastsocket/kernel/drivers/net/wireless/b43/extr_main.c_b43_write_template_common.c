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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct b43_wldev {int dummy; } ;
struct b43_plcp_hdr6 {int dummy; } ;
struct b43_plcp_hdr4 {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_SHM_SHARED ; 
 scalar_t__ FCS_LEN ; 
 int /*<<< orphan*/  b43_generate_plcp_hdr (struct b43_plcp_hdr4*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  b43_ram_write (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_shm_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int le32_to_cpu (scalar_t__) ; 

__attribute__((used)) static void b43_write_template_common(struct b43_wldev *dev,
				      const u8 *data, u16 size,
				      u16 ram_offset,
				      u16 shm_size_offset, u8 rate)
{
	u32 i, tmp;
	struct b43_plcp_hdr4 plcp;

	plcp.data = 0;
	b43_generate_plcp_hdr(&plcp, size + FCS_LEN, rate);
	b43_ram_write(dev, ram_offset, le32_to_cpu(plcp.data));
	ram_offset += sizeof(u32);
	/* The PLCP is 6 bytes long, but we only wrote 4 bytes, yet.
	 * So leave the first two bytes of the next write blank.
	 */
	tmp = (u32) (data[0]) << 16;
	tmp |= (u32) (data[1]) << 24;
	b43_ram_write(dev, ram_offset, tmp);
	ram_offset += sizeof(u32);
	for (i = 2; i < size; i += sizeof(u32)) {
		tmp = (u32) (data[i + 0]);
		if (i + 1 < size)
			tmp |= (u32) (data[i + 1]) << 8;
		if (i + 2 < size)
			tmp |= (u32) (data[i + 2]) << 16;
		if (i + 3 < size)
			tmp |= (u32) (data[i + 3]) << 24;
		b43_ram_write(dev, ram_offset + i - 2, tmp);
	}
	b43_shm_write16(dev, B43_SHM_SHARED, shm_size_offset,
			size + sizeof(struct b43_plcp_hdr6));
}