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
struct spec_name {char const* name; } ;
struct elfdump {int /*<<< orphan*/  snl; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct spec_name*,int /*<<< orphan*/ ) ; 
 scalar_t__ find_name (struct elfdump*,char const*) ; 
 struct spec_name* malloc (int) ; 
 int /*<<< orphan*/  sn_list ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void
add_name(struct elfdump *ed, const char *name)
{
	struct spec_name *sn;

	if (find_name(ed, name))
		return;
	if ((sn = malloc(sizeof(*sn))) == NULL) {
		warn("malloc failed");
		return;
	}
	sn->name = name;
	STAILQ_INSERT_TAIL(&ed->snl, sn, sn_list);
}