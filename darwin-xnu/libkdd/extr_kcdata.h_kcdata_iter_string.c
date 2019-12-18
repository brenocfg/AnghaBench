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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  kcdata_iter_t ;

/* Variables and functions */
 scalar_t__ kcdata_iter_payload (int /*<<< orphan*/ ) ; 
 scalar_t__ kcdata_iter_size (int /*<<< orphan*/ ) ; 
 scalar_t__ strnlen (char*,scalar_t__) ; 

__attribute__((used)) static inline
char *kcdata_iter_string(kcdata_iter_t iter, uint32_t offset) {
	if (offset > kcdata_iter_size(iter)) {
		return NULL;
	}
	uint32_t maxlen = kcdata_iter_size(iter) - offset;
	char *s = ((char*)kcdata_iter_payload(iter)) + offset;
	if (strnlen(s, maxlen) < maxlen) {
		return s;
	} else {
		return NULL;
	}
}