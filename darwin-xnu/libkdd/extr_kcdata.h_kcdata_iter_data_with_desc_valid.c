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
 int KCDATA_DESC_MAXLEN ; 
 scalar_t__ kcdata_iter_payload (int /*<<< orphan*/ ) ; 
 scalar_t__ kcdata_iter_size (int /*<<< orphan*/ ) ; 
 scalar_t__ kcdata_iter_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
int kcdata_iter_data_with_desc_valid(kcdata_iter_t iter, uint32_t minsize) {
	return
		kcdata_iter_valid(iter) &&
		kcdata_iter_size(iter) >= KCDATA_DESC_MAXLEN + minsize &&
		((char*)kcdata_iter_payload(iter))[KCDATA_DESC_MAXLEN-1] == 0;
}