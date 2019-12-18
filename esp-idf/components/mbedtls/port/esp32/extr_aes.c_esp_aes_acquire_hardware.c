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
 int /*<<< orphan*/  periph_module_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 

void esp_aes_acquire_hardware( void )
{
    portENTER_CRITICAL(&aes_spinlock);

    /* Enable AES hardware */
    periph_module_enable(PERIPH_AES_MODULE);
}