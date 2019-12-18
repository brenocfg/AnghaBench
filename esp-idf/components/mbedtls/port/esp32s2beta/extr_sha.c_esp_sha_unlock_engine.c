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
typedef  int /*<<< orphan*/  esp_sha_type ;

/* Variables and functions */
 int /*<<< orphan*/  _lock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ets_sha_disable () ; 
 int /*<<< orphan*/  s_sha_lock ; 

void esp_sha_unlock_engine(esp_sha_type sha_type)
{
    ets_sha_disable();
    _lock_release(&s_sha_lock);
}