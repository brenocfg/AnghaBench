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
typedef  int /*<<< orphan*/  br_gcm_context ;

/* Variables and functions */
 int /*<<< orphan*/  br_gcm_get_tag (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  memcpy (void*,unsigned char*,size_t) ; 

void
br_gcm_get_tag_trunc(br_gcm_context *ctx, void *tag, size_t len)
{
	unsigned char tmp[16];

	br_gcm_get_tag(ctx, tmp);
	memcpy(tag, tmp, len);
}