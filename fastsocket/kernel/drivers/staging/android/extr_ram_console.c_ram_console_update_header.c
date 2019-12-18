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
typedef  int /*<<< orphan*/  uint8_t ;
struct ram_console_buffer {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECC_BLOCK_SIZE ; 
 int ECC_SIZE ; 
 struct ram_console_buffer* ram_console_buffer ; 
 int /*<<< orphan*/  ram_console_buffer_size ; 
 int /*<<< orphan*/  ram_console_encode_rs8 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ram_console_par_buffer ; 

__attribute__((used)) static void ram_console_update_header(void)
{
#ifdef CONFIG_ANDROID_RAM_CONSOLE_ERROR_CORRECTION
	struct ram_console_buffer *buffer = ram_console_buffer;
	uint8_t *par;
	par = ram_console_par_buffer +
	      DIV_ROUND_UP(ram_console_buffer_size, ECC_BLOCK_SIZE) * ECC_SIZE;
	ram_console_encode_rs8((uint8_t *)buffer, sizeof(*buffer), par);
#endif
}