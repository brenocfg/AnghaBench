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

/* Variables and functions */
 int EIO ; 
 int ENODATA ; 
 int ENOMEDIUM ; 
 int diag14 (int,int,int) ; 

__attribute__((used)) static int diag_position_to_record(int devno, int record)
{
	int cc;

	cc = diag14(record, devno, 0x28);
	switch (cc) {
	case 0:
		return 0;
	case 2:
		return -ENOMEDIUM;
	case 3:
		return -ENODATA; /* position beyond end of file */
	default:
		return -EIO;
	}
}