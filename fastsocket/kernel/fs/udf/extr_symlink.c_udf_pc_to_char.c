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
struct super_block {int dummy; } ;
struct pathComponent {int componentType; scalar_t__ lengthComponentIdent; int /*<<< orphan*/  componentIdent; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  udf_get_filename (struct super_block*,int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void udf_pc_to_char(struct super_block *sb, char *from, int fromlen,
			   char *to)
{
	struct pathComponent *pc;
	int elen = 0;
	char *p = to;

	while (elen < fromlen) {
		pc = (struct pathComponent *)(from + elen);
		switch (pc->componentType) {
		case 1:
			if (pc->lengthComponentIdent == 0) {
				p = to;
				*p++ = '/';
			}
			break;
		case 3:
			memcpy(p, "../", 3);
			p += 3;
			break;
		case 4:
			memcpy(p, "./", 2);
			p += 2;
			/* that would be . - just ignore */
			break;
		case 5:
			p += udf_get_filename(sb, pc->componentIdent, p,
					      pc->lengthComponentIdent);
			*p++ = '/';
			break;
		}
		elen += sizeof(struct pathComponent) + pc->lengthComponentIdent;
	}
	if (p > to + 1)
		p[-1] = '\0';
	else
		p[0] = '\0';
}