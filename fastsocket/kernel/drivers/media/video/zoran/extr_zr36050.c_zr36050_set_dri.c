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
struct zr36050 {int dri; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZR050_DRI_IDX ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ) ; 
 int zr36050_pushit (struct zr36050*,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int
zr36050_set_dri (struct zr36050 *ptr)
{
	char dri_data[6];	// max. size of register set

	dprintk(3, "%s: write DRI\n", ptr->name);
	dri_data[0] = 0xff;
	dri_data[1] = 0xdd;
	dri_data[2] = 0x00;
	dri_data[3] = 0x04;
	dri_data[4] = ptr->dri >> 8;
	dri_data[5] = ptr->dri & 0xff;
	return zr36050_pushit(ptr, ZR050_DRI_IDX, 6, dri_data);
}