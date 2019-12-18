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
typedef  int /*<<< orphan*/  u32 ;
struct fw_csr_iterator {int dummy; } ;

/* Variables and functions */
#define  CSR_SPECIFIER_ID 129 
#define  CSR_VERSION 128 
 int /*<<< orphan*/  fw_csr_iterator_init (struct fw_csr_iterator*,int /*<<< orphan*/ *) ; 
 scalar_t__ fw_csr_iterator_next (struct fw_csr_iterator*,int*,int*) ; 
 int sprintf (char*,char*,int,int) ; 

__attribute__((used)) static int units_sprintf(char *buf, u32 *directory)
{
	struct fw_csr_iterator ci;
	int key, value;
	int specifier_id = 0;
	int version = 0;

	fw_csr_iterator_init(&ci, directory);
	while (fw_csr_iterator_next(&ci, &key, &value)) {
		switch (key) {
		case CSR_SPECIFIER_ID:
			specifier_id = value;
			break;
		case CSR_VERSION:
			version = value;
			break;
		}
	}

	return sprintf(buf, "0x%06x:0x%06x ", specifier_id, version);
}