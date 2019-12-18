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
typedef  size_t uint16_t ;
struct readelf {size_t* vs; int vs_sz; size_t ver_sz; TYPE_2__* ver; TYPE_1__* vs_s; } ;
struct TYPE_4__ {char* name; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int VERSYM_HIDDEN ; 
 size_t VERSYM_VERSION ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  warnx (char*,size_t) ; 

__attribute__((used)) static void
dump_versym(struct readelf *re)
{
	int i;
	uint16_t vs;

	if (re->vs_s == NULL || re->ver == NULL || re->vs == NULL)
		return;
	printf("\nVersion symbol section (%s):\n", re->vs_s->name);
	for (i = 0; i < re->vs_sz; i++) {
		if ((i & 3) == 0) {
			if (i > 0)
				putchar('\n');
			printf("  %03x:", i);
		}
		vs = re->vs[i] & VERSYM_VERSION;
		if (vs >= re->ver_sz || re->ver[vs].name == NULL) {
			warnx("invalid versym version index %u", re->vs[i]);
			break;
		}
		if (re->vs[i] & VERSYM_HIDDEN)
			printf(" %3xh %-12s ", vs,
			    re->ver[re->vs[i] & VERSYM_VERSION].name);
		else
			printf(" %3x %-12s ", vs, re->ver[re->vs[i]].name);
	}
	putchar('\n');
}