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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static inline u8 nes_get_encoded_size(int *size)
{
	u8 encoded_size = 0;
	if (*size <= 32) {
		*size = 32;
		encoded_size = 1;
	} else if (*size <= 128) {
		*size = 128;
		encoded_size = 2;
	} else if (*size <= 512) {
		*size = 512;
		encoded_size = 3;
	}
	return (encoded_size);
}