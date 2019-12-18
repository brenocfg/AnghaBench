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
struct isac {int type; int /*<<< orphan*/  (* write_isac ) (struct isac*,int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  DBG_L1M ; 
 int /*<<< orphan*/  ISACSX_CIX0 ; 
 int /*<<< orphan*/  ISAC_CIX0 ; 
#define  TYPE_ISAC 129 
#define  TYPE_ISACSX 128 
 int /*<<< orphan*/  stub1 (struct isac*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub2 (struct isac*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void ph_command(struct isac *isac, unsigned int command)
{
	DBG(DBG_L1M, "ph_command %#x", command);
	switch (isac->type) {
	case TYPE_ISAC:
		isac->write_isac(isac, ISAC_CIX0, (command << 2) | 3);
		break;
	case TYPE_ISACSX:
		isac->write_isac(isac, ISACSX_CIX0, (command << 4) | (7 << 1));
		break;
	}
}