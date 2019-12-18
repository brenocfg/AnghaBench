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
 int /*<<< orphan*/  AES_BLOCK_BYTES ; 
 int /*<<< orphan*/  AES_STATE_REG ; 
 scalar_t__ AES_TEXT_IN_BASE ; 
 scalar_t__ AES_TEXT_OUT_BASE ; 
 int /*<<< orphan*/  AES_TRIGGER_REG ; 
 scalar_t__ REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void esp_aes_block(const void *input, void *output)
{
    memcpy((void *)AES_TEXT_IN_BASE, input, AES_BLOCK_BYTES);

    REG_WRITE(AES_TRIGGER_REG, 1);
    while (REG_READ(AES_STATE_REG) != 0) { }

    memcpy(output, (void *)AES_TEXT_OUT_BASE, AES_BLOCK_BYTES);
}