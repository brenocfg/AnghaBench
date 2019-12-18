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

/* Variables and functions */
 int /*<<< orphan*/  esp_random () ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (void*,int,size_t) ; 

__attribute__((used)) static void bt_rand(void *buf, size_t len)
{
    if (!len) {
        return;
    }
    // Reset the buf value to the fixed value.
    memset(buf, 0x55, len);

    for (int i = 0; i < (int)(len / sizeof(uint32_t)); i++) {
        uint32_t rand = esp_random();
        memcpy(buf + i*sizeof(uint32_t), &rand, sizeof(uint32_t));
    }

    return;
}