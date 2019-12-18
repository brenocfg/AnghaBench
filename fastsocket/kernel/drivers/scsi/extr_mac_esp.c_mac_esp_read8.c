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
typedef  int /*<<< orphan*/  u8 ;
struct esp {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  nubus_readb (scalar_t__) ; 

__attribute__((used)) static inline u8 mac_esp_read8(struct esp *esp, unsigned long reg)
{
	return nubus_readb(esp->regs + reg * 16);
}