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
struct timespec {int dummy; } ;
struct pstore_info {int dummy; } ;
typedef  int ssize_t ;
typedef  enum pstore_type_id { ____Placeholder_pstore_type_id } pstore_type_id ;

/* Variables and functions */

__attribute__((used)) static ssize_t efi_pstore_read(u64 *id, enum pstore_type_id *type, int *count,
			       struct timespec *timespec,
			       char **buf, struct pstore_info *psi)
{
	return -1;
}