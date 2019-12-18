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
struct msn_entry {int eaz; struct msn_entry* next; int /*<<< orphan*/  msn; } ;
struct TYPE_3__ {struct msn_entry* msn_list; } ;
typedef  TYPE_1__ act2000_card ;
typedef  int __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static __u16
act2000_find_msn(act2000_card *card, char *msn, int ia5)
{
        struct msn_entry *p = card->msn_list;
	__u8 eaz = '0';

	while (p) {
		if (!strcmp(p->msn, msn)) {
			eaz = p->eaz;
			break;
		}
		p = p->next;
	}
	if (!ia5)
		return (1 << (eaz - '0'));
	else
		return eaz;
}