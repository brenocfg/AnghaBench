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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint64_t ;
struct flag_desc {int flag; char* desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dump_flags(struct flag_desc *desc, uint64_t val)
{
	struct flag_desc *fd;

	for (fd = desc; fd->flag != 0; fd++) {
		if (val & fd->flag) {
			val &= ~fd->flag;
			printf(" %s", fd->desc);
		}
	}
	if (val != 0)
		printf(" unknown (0x%jx)", (uintmax_t)val);
	printf("\n");
}