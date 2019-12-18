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
struct escd_info_struc {int min_escd_write_size; int escd_size; int nv_storage_base; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ pnp_bios_escd_info (struct escd_info_struc*) ; 
 int snprintf (char*,int,char*,int,int,int) ; 

__attribute__((used)) static int proc_read_escdinfo(char *buf, char **start, off_t pos,
			      int count, int *eof, void *data)
{
	struct escd_info_struc escd;

	if (pnp_bios_escd_info(&escd))
		return -EIO;
	return snprintf(buf, count,
			"min_ESCD_write_size %d\n"
			"ESCD_size %d\n"
			"NVRAM_base 0x%x\n",
			escd.min_escd_write_size,
			escd.escd_size, escd.nv_storage_base);
}