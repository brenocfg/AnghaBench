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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  kcdata_iter_t ;

/* Variables and functions */
 scalar_t__ kcdata_iter_payload (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
uint32_t kcdata_iter_container_type(kcdata_iter_t iter) {
	return * (uint32_t *) kcdata_iter_payload(iter);
}