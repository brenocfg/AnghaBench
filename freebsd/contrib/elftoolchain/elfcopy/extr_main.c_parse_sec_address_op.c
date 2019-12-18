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
typedef  void* uint64_t ;
struct sec_action {int setlma; int setvma; void* vma_adjust; void* lma_adjust; void* vma; void* lma; } ;
struct elfcopy {int dummy; } ;
typedef  void* int64_t ;

/* Variables and functions */
 int ECP_CHANGE_SEC_ADDR ; 
 int ECP_CHANGE_SEC_LMA ; 
 int ECP_CHANGE_SEC_VMA ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*) ; 
 struct sec_action* lookup_sec_act (struct elfcopy*,char const*,int) ; 
 int /*<<< orphan*/  strtoll (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoull (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parse_sec_address_op(struct elfcopy *ecp, int optnum, const char *optname,
    char *s)
{
	struct sec_action	*sac;
	const char		*name;
	char			*v;
	char			 op;

	name = v = s;
	do {
		v++;
	} while (*v != '\0' && *v != '=' && *v != '+' && *v != '-');
	if (*v == '\0' || *(v + 1) == '\0')
		errx(EXIT_FAILURE, "invalid format for %s", optname);
	op = *v;
	*v++ = '\0';
	sac = lookup_sec_act(ecp, name, 1);
	switch (op) {
	case '=':
		if (optnum == ECP_CHANGE_SEC_LMA ||
		    optnum == ECP_CHANGE_SEC_ADDR) {
			sac->setlma = 1;
			sac->lma = (uint64_t) strtoull(v, NULL, 0);
		}
		if (optnum == ECP_CHANGE_SEC_VMA ||
		    optnum == ECP_CHANGE_SEC_ADDR) {
			sac->setvma = 1;
			sac->vma = (uint64_t) strtoull(v, NULL, 0);
		}
		break;
	case '+':
		if (optnum == ECP_CHANGE_SEC_LMA ||
		    optnum == ECP_CHANGE_SEC_ADDR)
			sac->lma_adjust = (int64_t) strtoll(v, NULL, 0);
		if (optnum == ECP_CHANGE_SEC_VMA ||
		    optnum == ECP_CHANGE_SEC_ADDR)
			sac->vma_adjust = (int64_t) strtoll(v, NULL, 0);
		break;
	case '-':
		if (optnum == ECP_CHANGE_SEC_LMA ||
		    optnum == ECP_CHANGE_SEC_ADDR)
			sac->lma_adjust = (int64_t) -strtoll(v, NULL, 0);
		if (optnum == ECP_CHANGE_SEC_VMA ||
		    optnum == ECP_CHANGE_SEC_ADDR)
			sac->vma_adjust = (int64_t) -strtoll(v, NULL, 0);
		break;
	default:
		break;
	}
}