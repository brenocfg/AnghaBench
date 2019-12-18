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
struct b43_pio_txqueue {int rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_PIO8_TXCTL ; 
 int B43_PIO8_TXCTL_SUSPREQ ; 
 int /*<<< orphan*/  B43_PIO_TXCTL ; 
 int B43_PIO_TXCTL_SUSPREQ ; 
 int b43_piotx_read16 (struct b43_pio_txqueue*,int /*<<< orphan*/ ) ; 
 int b43_piotx_read32 (struct b43_pio_txqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_piotx_write16 (struct b43_pio_txqueue*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_piotx_write32 (struct b43_pio_txqueue*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_pio_tx_resume_queue(struct b43_pio_txqueue *q)
{
	if (q->rev >= 8) {
		b43_piotx_write32(q, B43_PIO8_TXCTL,
				  b43_piotx_read32(q, B43_PIO8_TXCTL)
				  & ~B43_PIO8_TXCTL_SUSPREQ);
	} else {
		b43_piotx_write16(q, B43_PIO_TXCTL,
				  b43_piotx_read16(q, B43_PIO_TXCTL)
				  & ~B43_PIO_TXCTL_SUSPREQ);
	}
}