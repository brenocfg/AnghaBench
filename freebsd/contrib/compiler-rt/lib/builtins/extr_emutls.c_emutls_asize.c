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
typedef  int /*<<< orphan*/  emutls_address_array ;

/* Variables and functions */

__attribute__((used)) static __inline uintptr_t emutls_asize(uintptr_t N) {
  return N * sizeof(void *) + sizeof(emutls_address_array);
}