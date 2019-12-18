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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__* data; } ;
struct TYPE_4__ {TYPE_1__ leaf; } ;
struct csr1212_keyval {TYPE_2__ value; } ;

/* Variables and functions */
 scalar_t__* CSR1212_TEXTUAL_DESCRIPTOR_LEAF_DATA (struct csr1212_keyval*) ; 
 scalar_t__ CSR1212_TEXTUAL_DESCRIPTOR_LEAF_OVERHEAD ; 
 size_t bytes_to_quads (size_t) ; 
 scalar_t__ csr1212_check_minimal_ascii (char const*) ; 
 struct csr1212_keyval* csr1212_new_descriptor_leaf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,size_t) ; 
 scalar_t__ quads_to_bytes (size_t) ; 
 size_t strlen (char const*) ; 

struct csr1212_keyval *csr1212_new_string_descriptor_leaf(const char *s)
{
	struct csr1212_keyval *kv;
	u32 *text;
	size_t str_len, quads;

	if (!s || !*s || csr1212_check_minimal_ascii(s))
		return NULL;

	str_len = strlen(s);
	quads = bytes_to_quads(str_len);
	kv = csr1212_new_descriptor_leaf(0, 0, NULL, quads_to_bytes(quads) +
				      CSR1212_TEXTUAL_DESCRIPTOR_LEAF_OVERHEAD);
	if (!kv)
		return NULL;

	kv->value.leaf.data[1] = 0;	/* width, character_set, language */
	text = CSR1212_TEXTUAL_DESCRIPTOR_LEAF_DATA(kv);
	text[quads - 1] = 0;		/* padding */
	memcpy(text, s, str_len);

	return kv;
}