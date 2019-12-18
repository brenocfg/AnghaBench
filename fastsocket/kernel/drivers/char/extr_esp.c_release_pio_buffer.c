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
struct esp_pio_buffer {struct esp_pio_buffer* next; } ;

/* Variables and functions */
 struct esp_pio_buffer* free_pio_buf ; 
 int /*<<< orphan*/  pio_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void release_pio_buffer(struct esp_pio_buffer *buf)
{
	unsigned long flags;
	spin_lock_irqsave(&pio_lock, flags);
	buf->next = free_pio_buf;
	free_pio_buf = buf;
	spin_unlock_irqrestore(&pio_lock, flags);
}