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
struct csr1212_keyval {int dummy; } ;

/* Variables and functions */
 int __csr1212_attach_keyval_to_directory (struct csr1212_keyval*,struct csr1212_keyval*,int) ; 

int csr1212_attach_keyval_to_directory(struct csr1212_keyval *dir,
				       struct csr1212_keyval *kv)
{
	return __csr1212_attach_keyval_to_directory(dir, kv, true);
}