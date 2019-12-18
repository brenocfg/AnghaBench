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
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  brcmjpeg_lock ; 
 int /*<<< orphan*/  vcos_mutex_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcmjpeg_init_once(void)
{
   vcos_mutex_create(&brcmjpeg_lock, VCOS_FUNCTION);
}