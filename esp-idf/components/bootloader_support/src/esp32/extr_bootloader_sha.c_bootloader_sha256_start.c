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
typedef  int /*<<< orphan*/  bootloader_sha256_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ets_sha_enable () ; 
 scalar_t__ words_hashed ; 

bootloader_sha256_handle_t bootloader_sha256_start(void)
{
    // Enable SHA hardware
    ets_sha_enable();
    words_hashed = 0;
    return (bootloader_sha256_handle_t)&words_hashed; // Meaningless non-NULL value
}