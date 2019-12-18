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
 int /*<<< orphan*/  CONFIG_FILE_PATH ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * config ; 
 int /*<<< orphan*/  config_save (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void btc_config_flush(void)
{
    assert(config != NULL);

    config_save(config, CONFIG_FILE_PATH);
}