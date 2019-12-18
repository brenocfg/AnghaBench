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
typedef  int /*<<< orphan*/  pegasus_t ;
typedef  int __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 int BMSR_MEDIA ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  read_mii_word (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static __u8 mii_phy_probe(pegasus_t * pegasus)
{
	int i;
	__u16 tmp;

	for (i = 0; i < 32; i++) {
		read_mii_word(pegasus, i, MII_BMSR, &tmp);
		if (tmp == 0 || tmp == 0xffff || (tmp & BMSR_MEDIA) == 0)
			continue;
		else
			return i;
	}

	return 0xff;
}