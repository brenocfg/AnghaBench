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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_1__ mz_crypt_sha ;

/* Variables and functions */

void mz_crypt_sha_set_algorithm(void *handle, uint16_t algorithm)
{
    mz_crypt_sha *sha = (mz_crypt_sha *)handle;
    sha->algorithm = algorithm;
}