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
struct readelf {scalar_t__ ver_sz; int /*<<< orphan*/ * ver; scalar_t__ vs_sz; int /*<<< orphan*/ * vs; int /*<<< orphan*/ * vs_s; int /*<<< orphan*/ * vn_s; int /*<<< orphan*/ * vd_s; scalar_t__ shnum; int /*<<< orphan*/ * sl; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
unload_sections(struct readelf *re)
{

	if (re->sl != NULL) {
		free(re->sl);
		re->sl = NULL;
	}
	re->shnum = 0;
	re->vd_s = NULL;
	re->vn_s = NULL;
	re->vs_s = NULL;
	re->vs = NULL;
	re->vs_sz = 0;
	if (re->ver != NULL) {
		free(re->ver);
		re->ver = NULL;
		re->ver_sz = 0;
	}
}