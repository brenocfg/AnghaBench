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
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ mz_crypt_aes ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */

void mz_crypt_aes_set_mode(void *handle, int32_t mode)
{
    mz_crypt_aes *aes = (mz_crypt_aes *)handle;
    aes->mode = mode;
}