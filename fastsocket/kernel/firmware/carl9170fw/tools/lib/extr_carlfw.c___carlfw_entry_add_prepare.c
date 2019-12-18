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
struct carlfw_list_entry {int /*<<< orphan*/  data; } ;
struct carlfw {unsigned int desc_list_len; int /*<<< orphan*/  desc_list_entries; } ;
struct carl9170fw_desc_head {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct carlfw_list_entry* ERR_PTR (int /*<<< orphan*/ ) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct carlfw_list_entry* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct carl9170fw_desc_head const*,unsigned int) ; 

__attribute__((used)) static struct carlfw_list_entry *__carlfw_entry_add_prepare(struct carlfw *fw,
	const struct carl9170fw_desc_head *desc)
{
	struct carlfw_list_entry *tmp;
	unsigned int len;

	len = le16_to_cpu(desc->length);

	if (len < sizeof(struct carl9170fw_desc_head))
		return ERR_PTR(-EINVAL);

	tmp = malloc(sizeof(*tmp) + len);
	if (!tmp)
		return ERR_PTR(-ENOMEM);

	fw->desc_list_entries++;
	fw->desc_list_len += len;

	memcpy(tmp->data, desc, len);
	return tmp;
}