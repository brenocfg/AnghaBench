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

/* Variables and functions */
 scalar_t__ esp_efuse_read_secure_version () ; 

bool esp_efuse_check_secure_version(uint32_t secure_version)
{
    uint32_t sec_ver_hw = esp_efuse_read_secure_version();
    return secure_version >= sec_ver_hw;
}