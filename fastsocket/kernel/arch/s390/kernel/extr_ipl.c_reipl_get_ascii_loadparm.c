#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  load_parm; } ;
struct TYPE_4__ {TYPE_1__ ccw; } ;
struct ipl_parameter_block {TYPE_2__ ipl_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBCASC (char*,size_t) ; 
 size_t LOADPARM_LEN ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  strstrip (char*) ; 

__attribute__((used)) static void reipl_get_ascii_loadparm(char *loadparm,
				     struct ipl_parameter_block *ibp)
{
	memcpy(loadparm, ibp->ipl_info.ccw.load_parm, LOADPARM_LEN);
	EBCASC(loadparm, LOADPARM_LEN);
	loadparm[LOADPARM_LEN] = 0;
	strstrip(loadparm);
}