#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rc4_key_st {int dummy; } ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  Rc4Key; } ;
typedef  TYPE_1__ CRYPT ;

/* Variables and functions */
 int /*<<< orphan*/  Malloc (int) ; 
 int /*<<< orphan*/  RC4_set_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* ZeroMalloc (int) ; 

CRYPT *NewCrypt(void *key, UINT size)
{
	CRYPT *c = ZeroMalloc(sizeof(CRYPT));

	c->Rc4Key = Malloc(sizeof(struct rc4_key_st));

	RC4_set_key(c->Rc4Key, size, (UCHAR *)key);

	return c;
}