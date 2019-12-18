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
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int IOAT3_DCA_GREQID_OFFSET ; 
 int IOAT_DCA_GREQID_LASTID ; 
 int readl (void*) ; 
 int readw (void*) ; 

__attribute__((used)) static int ioat3_dca_count_dca_slots(void *iobase, u16 dca_offset)
{
	int slots = 0;
	u32 req;
	u16 global_req_table;

	global_req_table = readw(iobase + dca_offset + IOAT3_DCA_GREQID_OFFSET);
	if (global_req_table == 0)
		return 0;

	do {
		req = readl(iobase + global_req_table + (slots * sizeof(u32)));
		slots++;
	} while ((req & IOAT_DCA_GREQID_LASTID) == 0);

	return slots;
}