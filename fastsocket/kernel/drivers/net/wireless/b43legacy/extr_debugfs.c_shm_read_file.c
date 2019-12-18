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
typedef  int /*<<< orphan*/  tmp ;
struct b43legacy_wldev {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_SHM_SHARED ; 
 int /*<<< orphan*/  b43legacy_shm_read16 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t shm_read_file(struct b43legacy_wldev *dev, char *buf, size_t bufsize)
{
	ssize_t count = 0;
	int i;
	u16 tmp;
	__le16 *le16buf = (__le16 *)buf;

	for (i = 0; i < 0x1000; i++) {
		if (bufsize < sizeof(tmp))
			break;
		tmp = b43legacy_shm_read16(dev, B43legacy_SHM_SHARED, 2 * i);
		le16buf[i] = cpu_to_le16(tmp);
		count += sizeof(tmp);
		bufsize -= sizeof(tmp);
	}

	return count;
}