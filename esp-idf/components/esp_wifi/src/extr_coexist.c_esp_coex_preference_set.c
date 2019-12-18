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
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  scalar_t__ esp_coex_prefer_t ;
typedef  int /*<<< orphan*/  coex_prefer_t ;

/* Variables and functions */
 int /*<<< orphan*/  coex_preference_set (int /*<<< orphan*/ ) ; 

esp_err_t esp_coex_preference_set(esp_coex_prefer_t prefer)
{
    return coex_preference_set((coex_prefer_t)prefer);
}