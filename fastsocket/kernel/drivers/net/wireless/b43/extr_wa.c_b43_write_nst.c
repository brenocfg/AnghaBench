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
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_OFDMTAB_NOISESCALE ; 
 int B43_TAB_NOISESCALE_SIZE ; 
 int /*<<< orphan*/  b43_ofdmtab_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void b43_write_nst(struct b43_wldev *dev, const u16 *nst)
{
	int i;

	for (i = 0; i < B43_TAB_NOISESCALE_SIZE; i++)
		b43_ofdmtab_write16(dev, B43_OFDMTAB_NOISESCALE, i, nst[i]);
}