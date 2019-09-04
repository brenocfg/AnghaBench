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
typedef  int /*<<< orphan*/  VDPAUHWContext ;
typedef  int /*<<< orphan*/  AVVDPAUContext ;

/* Variables and functions */
 int /*<<< orphan*/ * av_mallocz (int) ; 

AVVDPAUContext *av_vdpau_alloc_context(void)
{
    return av_mallocz(sizeof(VDPAUHWContext));
}