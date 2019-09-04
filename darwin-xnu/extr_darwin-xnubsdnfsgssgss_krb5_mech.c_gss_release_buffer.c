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
typedef  scalar_t__ uint32_t ;
typedef  TYPE_1__* gss_buffer_t ;
struct TYPE_3__ {scalar_t__ length; int /*<<< orphan*/ * value; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GSS_S_COMPLETE ; 
 int /*<<< orphan*/  M_TEMP ; 

uint32_t
gss_release_buffer(uint32_t *minor, gss_buffer_t buf)
{
	if (minor)
		*minor = 0;
	if (buf->value)
		FREE(buf->value, M_TEMP);
	buf->value = NULL;
	buf->length = 0;
	return (GSS_S_COMPLETE);
}