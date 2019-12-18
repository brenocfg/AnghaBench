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
struct ram_console_buffer {int start; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int ECC_BLOCK_SIZE ; 
 int ECC_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,unsigned int) ; 
 struct ram_console_buffer* ram_console_buffer ; 
 int ram_console_buffer_size ; 
 int /*<<< orphan*/  ram_console_encode_rs8 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ram_console_par_buffer ; 

__attribute__((used)) static void ram_console_update(const char *s, unsigned int count)
{
	struct ram_console_buffer *buffer = ram_console_buffer;
#ifdef CONFIG_ANDROID_RAM_CONSOLE_ERROR_CORRECTION
	uint8_t *buffer_end = buffer->data + ram_console_buffer_size;
	uint8_t *block;
	uint8_t *par;
	int size = ECC_BLOCK_SIZE;
#endif
	memcpy(buffer->data + buffer->start, s, count);
#ifdef CONFIG_ANDROID_RAM_CONSOLE_ERROR_CORRECTION
	block = buffer->data + (buffer->start & ~(ECC_BLOCK_SIZE - 1));
	par = ram_console_par_buffer +
	      (buffer->start / ECC_BLOCK_SIZE) * ECC_SIZE;
	do {
		if (block + ECC_BLOCK_SIZE > buffer_end)
			size = buffer_end - block;
		ram_console_encode_rs8(block, size, par);
		block += ECC_BLOCK_SIZE;
		par += ECC_SIZE;
	} while (block < buffer->data + buffer->start + count);
#endif
}