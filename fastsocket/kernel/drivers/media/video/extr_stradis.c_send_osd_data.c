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
struct saa7146 {int osdtail; int osdhead; int /*<<< orphan*/ * osdbuf; int /*<<< orphan*/  dmadebi; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBM_MP2_MASK0 ; 
 int /*<<< orphan*/  IBM_MP2_OSD_ADDR ; 
 int /*<<< orphan*/  IBM_MP2_OSD_DATA ; 
 int /*<<< orphan*/  debNormal ; 
 int /*<<< orphan*/  debiwrite (struct saa7146*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void send_osd_data(struct saa7146 *saa)
{
	int size = saa->osdtail - saa->osdhead;
	if (size > 30720)
		size = 30720;
	/* ensure some multiple of 8 bytes is transferred */
	size = 8 * ((size + 8) >> 3);
	if (size) {
		debiwrite(saa, debNormal, IBM_MP2_OSD_ADDR,
			  (saa->osdhead >> 3), 2);
		memcpy(saa->dmadebi, &saa->osdbuf[saa->osdhead], size);
		saa->osdhead += size;
		/* block transfer of next 8 bytes to ~32k bytes */
		debiwrite(saa, debNormal, IBM_MP2_OSD_DATA, 0, size);
	}
	if (saa->osdhead >= saa->osdtail) {
		saa->osdhead = saa->osdtail = 0;
		debiwrite(saa, debNormal, IBM_MP2_MASK0, 0xc00c, 2);
	}
}