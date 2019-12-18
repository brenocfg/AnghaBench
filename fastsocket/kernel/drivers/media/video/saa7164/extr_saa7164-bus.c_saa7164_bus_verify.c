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
struct tmComResBusInfo {scalar_t__ m_dwSizeSetRing; scalar_t__ m_dwSizeGetRing; int /*<<< orphan*/  m_dwGetWritePos; int /*<<< orphan*/  m_dwGetReadPos; int /*<<< orphan*/  m_dwSetWritePos; int /*<<< orphan*/  m_dwSetReadPos; } ;
struct saa7164_dev {struct tmComResBusInfo bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  saa7164_bus_dump (struct saa7164_dev*) ; 
 scalar_t__ saa7164_readl (int /*<<< orphan*/ ) ; 
 int saa_debug ; 

void saa7164_bus_verify(struct saa7164_dev *dev)
{
	struct tmComResBusInfo *b = &dev->bus;
	int bug = 0;

	if (saa7164_readl(b->m_dwSetReadPos) > b->m_dwSizeSetRing)
		bug++;

	if (saa7164_readl(b->m_dwSetWritePos) > b->m_dwSizeSetRing)
		bug++;

	if (saa7164_readl(b->m_dwGetReadPos) > b->m_dwSizeGetRing)
		bug++;

	if (saa7164_readl(b->m_dwGetWritePos) > b->m_dwSizeGetRing)
		bug++;

	if (bug) {
		saa_debug = 0xffff; /* Ensure we get the bus dump */
		saa7164_bus_dump(dev);
		saa_debug = 1024; /* Ensure we get the bus dump */
		BUG();
	}
}