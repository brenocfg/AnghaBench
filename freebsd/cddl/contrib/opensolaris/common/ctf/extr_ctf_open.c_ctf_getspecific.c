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
struct TYPE_3__ {void* ctf_specific; } ;
typedef  TYPE_1__ ctf_file_t ;

/* Variables and functions */

void *
ctf_getspecific(ctf_file_t *fp)
{
	return (fp->ctf_specific);
}