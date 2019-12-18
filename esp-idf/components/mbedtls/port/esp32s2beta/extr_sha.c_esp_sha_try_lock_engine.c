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
 scalar_t__ _lock_try_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_sha_lock_engine_inner () ; 
 int /*<<< orphan*/  s_sha_lock ; 

bool esp_sha_try_lock_engine(esp_sha_type sha_type)
{
  if(_lock_try_acquire(&s_sha_lock) != 0) {
        /* SHA engine is already in use */
        return false;
    } else {
        esp_sha_lock_engine_inner();
        return true;
    }
}