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

__attribute__((used)) static __inline uintptr_t emutls_new_data_array_size(uintptr_t index) {
  // Need to allocate emutls_address_array with extra slots
  // to store the header.
  // Round up the emutls_address_array size to multiple of 16.
  uintptr_t header_words = sizeof(emutls_address_array) / sizeof(void *);
  return ((index + header_words + 15) & ~((uintptr_t)15)) - header_words;
}