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
typedef  int /*<<< orphan*/  u64 ;
struct pstore_info {int dummy; } ;
typedef  enum pstore_type_id { ____Placeholder_pstore_type_id } pstore_type_id ;
typedef  enum kmsg_dump_reason { ____Placeholder_kmsg_dump_reason } kmsg_dump_reason ;

/* Variables and functions */

__attribute__((used)) static int efi_pstore_write(enum pstore_type_id type,
		enum kmsg_dump_reason reason, u64 *id,
		unsigned int part, int count, size_t size,
		struct pstore_info *psi)
{
	return 0;
}