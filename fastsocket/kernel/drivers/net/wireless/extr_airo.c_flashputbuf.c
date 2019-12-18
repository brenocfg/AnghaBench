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
struct airo_info {int* flash; scalar_t__ pciaux; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUXDATA ; 
 int /*<<< orphan*/  AUXOFF ; 
 int /*<<< orphan*/  AUXPAGE ; 
 int /*<<< orphan*/  FLAG_MPI ; 
 int FLASHSIZE ; 
 int /*<<< orphan*/  OUT4500 (struct airo_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SWS0 ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,int*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int flashputbuf(struct airo_info *ai){
	int            nwords;

	/* Write stuff */
	if (test_bit(FLAG_MPI,&ai->flags))
		memcpy_toio(ai->pciaux + 0x8000, ai->flash, FLASHSIZE);
	else {
		OUT4500(ai,AUXPAGE,0x100);
		OUT4500(ai,AUXOFF,0);

		for(nwords=0;nwords != FLASHSIZE / 2;nwords++){
			OUT4500(ai,AUXDATA,ai->flash[nwords] & 0xffff);
		}
	}
	OUT4500(ai,SWS0,0x8000);

	return 0;
}