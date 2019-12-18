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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  Rc4Key; } ;
typedef  TYPE_1__ CRYPT ;

/* Variables and functions */
 int /*<<< orphan*/  RC4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*) ; 

void Encrypt(CRYPT *c, void *dst, void *src, UINT size)
{
	RC4(c->Rc4Key, size, src, dst);
}