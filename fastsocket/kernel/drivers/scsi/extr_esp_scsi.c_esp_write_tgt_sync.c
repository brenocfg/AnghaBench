#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct esp {scalar_t__ prev_soff; scalar_t__ prev_stp; TYPE_1__* target; } ;
struct TYPE_2__ {scalar_t__ esp_offset; scalar_t__ esp_period; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_SOFF ; 
 int /*<<< orphan*/  ESP_STP ; 
 int /*<<< orphan*/  esp_write8 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esp_write_tgt_sync(struct esp *esp, int tgt)
{
	u8 off = esp->target[tgt].esp_offset;
	u8 per = esp->target[tgt].esp_period;

	if (off != esp->prev_soff) {
		esp->prev_soff = off;
		esp_write8(off, ESP_SOFF);
	}
	if (per != esp->prev_stp) {
		esp->prev_stp = per;
		esp_write8(per, ESP_STP);
	}
}