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
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct esp_pio_buffer* free_pio_buf ; 
 struct esp_pio_buffer* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pio_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline struct esp_pio_buffer *get_pio_buffer(void)
{
	struct esp_pio_buffer *buf;
	unsigned long flags;

	spin_lock_irqsave(&pio_lock, flags);
	if (free_pio_buf) {
		buf = free_pio_buf;
		free_pio_buf = buf->next;
	} else {
		buf = kmalloc(sizeof(struct esp_pio_buffer), GFP_ATOMIC);
	}
	spin_unlock_irqrestore(&pio_lock, flags);
	return buf;
}