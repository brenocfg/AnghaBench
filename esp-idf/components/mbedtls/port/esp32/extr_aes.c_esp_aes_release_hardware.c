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

/* Variables and functions */
 int /*<<< orphan*/  PERIPH_AES_MODULE ; 
 int /*<<< orphan*/  aes_spinlock ; 
 int /*<<< orphan*/  periph_module_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 

void esp_aes_release_hardware( void )
{
    /* Disable AES hardware */
    periph_module_disable(PERIPH_AES_MODULE);

    portEXIT_CRITICAL(&aes_spinlock);
}