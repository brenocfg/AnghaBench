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
struct pda_custom_wrapper {int /*<<< orphan*/  data; int /*<<< orphan*/  offset; int /*<<< orphan*/  entry_size; int /*<<< orphan*/  entries; int /*<<< orphan*/  len; } ;
struct p54_cal_database {size_t entries; size_t entry_size; size_t offset; size_t len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct p54_cal_database* kmalloc (int,int /*<<< orphan*/ ) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static struct p54_cal_database *p54_convert_db(struct pda_custom_wrapper *src,
					       size_t total_len)
{
	struct p54_cal_database *dst;
	size_t payload_len, entries, entry_size, offset;

	payload_len = le16_to_cpu(src->len);
	entries = le16_to_cpu(src->entries);
	entry_size = le16_to_cpu(src->entry_size);
	offset = le16_to_cpu(src->offset);
	if (((entries * entry_size + offset) != payload_len) ||
	     (payload_len + sizeof(*src) != total_len))
		return NULL;

	dst = kmalloc(sizeof(*dst) + payload_len, GFP_KERNEL);
	if (!dst)
		return NULL;

	dst->entries = entries;
	dst->entry_size = entry_size;
	dst->offset = offset;
	dst->len = payload_len;

	memcpy(dst->data, src->data, payload_len);
	return dst;
}