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
struct TYPE_3__ {scalar_t__ count; int /*<<< orphan*/  val_sha1; int /*<<< orphan*/  val_md5; int /*<<< orphan*/ * vtable; } ;
typedef  TYPE_1__ br_md5sha1_context ;

/* Variables and functions */
 int /*<<< orphan*/  br_md5_IV ; 
 int /*<<< orphan*/  br_md5sha1_vtable ; 
 int /*<<< orphan*/  br_sha1_IV ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
br_md5sha1_init(br_md5sha1_context *cc)
{
	cc->vtable = &br_md5sha1_vtable;
	memcpy(cc->val_md5, br_md5_IV, sizeof cc->val_md5);
	memcpy(cc->val_sha1, br_sha1_IV, sizeof cc->val_sha1);
	cc->count = 0;
}