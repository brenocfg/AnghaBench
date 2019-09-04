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
struct so_procinfo {scalar_t__ spi_pid; scalar_t__ spi_delegated; scalar_t__ spi_epid; int /*<<< orphan*/  spi_euuid; int /*<<< orphan*/  spi_uuid; } ;
struct pktap_header {scalar_t__ pth_pid; scalar_t__* pth_comm; scalar_t__ pth_epid; scalar_t__* pth_ecomm; int /*<<< orphan*/  pth_euuid; int /*<<< orphan*/  pth_flags; int /*<<< orphan*/  pth_uuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAXCOMLEN ; 
 int /*<<< orphan*/  PTH_FLAG_PROC_DELEGATED ; 
 int /*<<< orphan*/  proc_name (scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pktap_set_procinfo(struct pktap_header *hdr, struct so_procinfo *soprocinfo)
{
	hdr->pth_pid = soprocinfo->spi_pid;
	if (hdr->pth_comm[0] == 0)
		proc_name(soprocinfo->spi_pid, hdr->pth_comm, MAXCOMLEN);
	if (soprocinfo->spi_pid != 0)
		uuid_copy(hdr->pth_uuid, soprocinfo->spi_uuid);

	if (soprocinfo->spi_delegated != 0) {
		hdr->pth_flags |= PTH_FLAG_PROC_DELEGATED;
		hdr->pth_epid = soprocinfo->spi_epid;
		if (hdr->pth_ecomm[0] == 0)
		proc_name(soprocinfo->spi_epid, hdr->pth_ecomm, MAXCOMLEN);
		uuid_copy(hdr->pth_euuid, soprocinfo->spi_euuid);
	}
}