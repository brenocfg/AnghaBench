#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct carlfw {int dummy; } ;
struct carl9170fw_fix_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;
struct carl9170fw_fix_desc {int /*<<< orphan*/ * data; TYPE_1__ head; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct carl9170fw_fix_desc*) ; 
 scalar_t__ PTR_ERR (struct carl9170fw_fix_desc*) ; 
 struct carl9170fw_fix_desc* carlfw_desc_mod_len (struct carlfw*,TYPE_1__*,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct carl9170fw_fix_entry*,int) ; 

__attribute__((used)) static int
add_another_fix_entry(struct carlfw *fw, struct carl9170fw_fix_desc *fix,
		 struct carl9170fw_fix_entry *fix_entry)
{
	unsigned int entry;

	fix = carlfw_desc_mod_len(fw, &fix->head, sizeof(*fix_entry));
	if (IS_ERR_OR_NULL(fix))
		return (int) PTR_ERR(fix);

	entry = (le16_to_cpu(fix->head.length) - sizeof(*fix)) /
		sizeof(*fix_entry) - 1;

	memcpy(&fix->data[entry], fix_entry, sizeof(*fix_entry));
	return 0;
}