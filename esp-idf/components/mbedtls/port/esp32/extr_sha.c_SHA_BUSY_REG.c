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
typedef  int esp_sha_type ;

/* Variables and functions */
 scalar_t__ SHA_1_BUSY_REG ; 

__attribute__((used)) inline static uint32_t SHA_BUSY_REG(esp_sha_type sha_type) {
    return SHA_1_BUSY_REG + sha_type * 0x10;
}