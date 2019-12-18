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
typedef  unsigned int u32 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 unsigned int B43_MAX_SHM_ADDR ; 
 unsigned int B43_MAX_SHM_ROUTING ; 
 unsigned int B43_SHM_SHARED ; 
 int E2BIG ; 
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 unsigned int b43_shm_read32 (struct b43_wldev*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  b43_shm_write32 (struct b43_wldev*,unsigned int,unsigned int,unsigned int) ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int shm32write__write_file(struct b43_wldev *dev,
				  const char *buf, size_t count)
{
	unsigned int routing, addr, mask, set;
	u32 val;
	int res;

	res = sscanf(buf, "0x%X 0x%X 0x%X 0x%X",
		     &routing, &addr, &mask, &set);
	if (res != 4)
		return -EINVAL;
	if (routing > B43_MAX_SHM_ROUTING)
		return -EADDRNOTAVAIL;
	if (addr > B43_MAX_SHM_ADDR)
		return -EADDRNOTAVAIL;
	if (routing == B43_SHM_SHARED) {
		if ((addr % 2) != 0)
			return -EADDRNOTAVAIL;
	}
	if ((mask > 0xFFFFFFFF) || (set > 0xFFFFFFFF))
		return -E2BIG;

	if (mask == 0)
		val = 0;
	else
		val = b43_shm_read32(dev, routing, addr);
	val &= mask;
	val |= set;
	b43_shm_write32(dev, routing, addr, val);

	return 0;
}