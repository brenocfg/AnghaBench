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
typedef  int /*<<< orphan*/  ccchacha20poly1305_fns_t ;
struct TYPE_2__ {int /*<<< orphan*/  ccchacha20poly1305_fns; } ;

/* Variables and functions */
 TYPE_1__* g_crypto_funcs ; 

__attribute__((used)) static ccchacha20poly1305_fns_t fns(void)
{
    return g_crypto_funcs->ccchacha20poly1305_fns;
}