#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  wifi_cfg; } ;
typedef  TYPE_1__ wifi_prov_ctx_t ;
typedef  int /*<<< orphan*/  wifi_config_t ;

/* Variables and functions */

__attribute__((used)) static wifi_config_t *get_config(wifi_prov_ctx_t **ctx)
{
    return (*ctx ? &(*ctx)->wifi_cfg : NULL);
}