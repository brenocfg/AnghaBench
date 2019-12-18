#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ptype; } ;
typedef  TYPE_1__ isdnloop_card ;

/* Variables and functions */
#define  ISDN_PTYPE_1TR6 129 
#define  ISDN_PTYPE_EURO 128 
 int* ctable_1t ; 
 int /*<<< orphan*/ * ctable_eu ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 

__attribute__((used)) static char *
isdnloop_unicause(isdnloop_card * card, int loc, int cau)
{
	static char buf[6];

	switch (card->ptype) {
		case ISDN_PTYPE_EURO:
			sprintf(buf, "E%02X%02X", (loc) ? 4 : 2, ctable_eu[cau]);
			break;
		case ISDN_PTYPE_1TR6:
			sprintf(buf, "%02X44", ctable_1t[cau]);
			break;
		default:
			return ("0000");
	}
	return (buf);
}