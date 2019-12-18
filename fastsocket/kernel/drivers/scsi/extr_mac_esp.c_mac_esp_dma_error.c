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
struct esp {int dummy; } ;
struct TYPE_2__ {int error; } ;

/* Variables and functions */
 TYPE_1__* MAC_ESP_GET_PRIV (struct esp*) ; 

__attribute__((used)) static int mac_esp_dma_error(struct esp *esp)
{
	return MAC_ESP_GET_PRIV(esp)->error;
}