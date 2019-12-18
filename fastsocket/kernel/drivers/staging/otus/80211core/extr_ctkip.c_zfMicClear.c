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
struct zsMicVar {scalar_t__ m; scalar_t__ nBytes; int /*<<< orphan*/  k1; int /*<<< orphan*/  right; int /*<<< orphan*/  k0; int /*<<< orphan*/  left; } ;

/* Variables and functions */

void zfMicClear(struct zsMicVar* pMic)
{
    pMic->left = pMic->k0;
    pMic->right = pMic->k1;
    pMic->nBytes = 0;
    pMic->m = 0;
}