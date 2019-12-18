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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ speed_map; scalar_t__ topology_map; } ;
struct hpsb_host {TYPE_1__ csr; } ;
typedef  int /*<<< orphan*/  quadlet_t ;

/* Variables and functions */
 int CSR_REGISTER_BASE ; 
 int CSR_SPEED_MAP ; 
 char* CSR_TOPOLOGY_MAP ; 
 int RCODE_COMPLETE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int read_maps(struct hpsb_host *host, int nodeid, quadlet_t *buffer,
                     u64 addr, size_t length, u16 fl)
{
	unsigned long flags;
        int csraddr = addr - CSR_REGISTER_BASE;
        const char *src;

        spin_lock_irqsave(&host->csr.lock, flags);

	if (csraddr < CSR_SPEED_MAP) {
                src = ((char *)host->csr.topology_map) + csraddr
                        - CSR_TOPOLOGY_MAP;
        } else {
                src = ((char *)host->csr.speed_map) + csraddr - CSR_SPEED_MAP;
        }

        memcpy(buffer, src, length);
        spin_unlock_irqrestore(&host->csr.lock, flags);
        return RCODE_COMPLETE;
}