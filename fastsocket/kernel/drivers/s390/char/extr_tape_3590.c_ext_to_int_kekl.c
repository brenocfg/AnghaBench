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
struct tape390_kekl {scalar_t__ type; scalar_t__ type_on_tape; int /*<<< orphan*/  label; } ;
struct tape3592_kekl {int flags; char* label; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASCEBC (char*,int) ; 
 scalar_t__ TAPE390_KEKL_TYPE_HASH ; 
 int /*<<< orphan*/  memset (struct tape3592_kekl*,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ext_to_int_kekl(struct tape390_kekl *in,
			    struct tape3592_kekl *out)
{
	int i;

	memset(out, 0, sizeof(*out));
	if (in->type == TAPE390_KEKL_TYPE_HASH)
		out->flags |= 0x40;
	if (in->type_on_tape == TAPE390_KEKL_TYPE_HASH)
		out->flags |= 0x80;
	strncpy(out->label, in->label, 64);
	for (i = strlen(in->label); i < sizeof(out->label); i++)
		out->label[i] = ' ';
	ASCEBC(out->label, sizeof(out->label));
}