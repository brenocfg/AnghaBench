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
struct tape390_kekl {int /*<<< orphan*/  label; void* type_on_tape; void* type; } ;
struct tape3592_kekl {int flags; int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBCASC (int /*<<< orphan*/ ,int) ; 
 void* TAPE390_KEKL_TYPE_HASH ; 
 void* TAPE390_KEKL_TYPE_LABEL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct tape390_kekl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strstrip (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void int_to_ext_kekl(struct tape3592_kekl *in,
			    struct tape390_kekl *out)
{
	memset(out, 0, sizeof(*out));
	if(in->flags & 0x40)
		out->type = TAPE390_KEKL_TYPE_HASH;
	else
		out->type = TAPE390_KEKL_TYPE_LABEL;
	if(in->flags & 0x80)
		out->type_on_tape = TAPE390_KEKL_TYPE_HASH;
	else
		out->type_on_tape = TAPE390_KEKL_TYPE_LABEL;
	memcpy(out->label, in->label, sizeof(in->label));
	EBCASC(out->label, sizeof(in->label));
	strstrip(out->label);
}