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
typedef  int u32 ;
struct ieee1394_device_id {int vendor_id; int model_id; int specifier_id; int version; } ;
struct fw_csr_iterator {int dummy; } ;

/* Variables and functions */
 int CSR_MODEL ; 
 int CSR_SPECIFIER_ID ; 
 int CSR_VENDOR ; 
 int CSR_VERSION ; 
 int IEEE1394_MATCH_MODEL_ID ; 
 int IEEE1394_MATCH_SPECIFIER_ID ; 
 int IEEE1394_MATCH_VENDOR_ID ; 
 int IEEE1394_MATCH_VERSION ; 
 int /*<<< orphan*/  fw_csr_iterator_init (struct fw_csr_iterator*,int*) ; 
 scalar_t__ fw_csr_iterator_next (struct fw_csr_iterator*,int*,int*) ; 

__attribute__((used)) static int match_unit_directory(u32 *directory, u32 match_flags,
				const struct ieee1394_device_id *id)
{
	struct fw_csr_iterator ci;
	int key, value, match;

	match = 0;
	fw_csr_iterator_init(&ci, directory);
	while (fw_csr_iterator_next(&ci, &key, &value)) {
		if (key == CSR_VENDOR && value == id->vendor_id)
			match |= IEEE1394_MATCH_VENDOR_ID;
		if (key == CSR_MODEL && value == id->model_id)
			match |= IEEE1394_MATCH_MODEL_ID;
		if (key == CSR_SPECIFIER_ID && value == id->specifier_id)
			match |= IEEE1394_MATCH_SPECIFIER_ID;
		if (key == CSR_VERSION && value == id->version)
			match |= IEEE1394_MATCH_VERSION;
	}

	return (match & match_flags) == match_flags;
}