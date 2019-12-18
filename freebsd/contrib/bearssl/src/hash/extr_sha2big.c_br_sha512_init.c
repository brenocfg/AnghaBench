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
struct TYPE_3__ {scalar_t__ count; int /*<<< orphan*/  val; int /*<<< orphan*/ * vtable; } ;
typedef  TYPE_1__ br_sha512_context ;

/* Variables and functions */
 int /*<<< orphan*/  IV512 ; 
 int /*<<< orphan*/  br_sha512_vtable ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
br_sha512_init(br_sha512_context *cc)
{
	cc->vtable = &br_sha512_vtable;
	memcpy(cc->val, IV512, sizeof IV512);
	cc->count = 0;
}