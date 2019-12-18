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

/* Variables and functions */
 int /*<<< orphan*/  DM_640x480 ; 
 int /*<<< orphan*/  PM_RGB565 ; 
 int /*<<< orphan*/  PVR_LIST_OP_POLY ; 
 int /*<<< orphan*/  PVR_LIST_PT_POLY ; 
 int /*<<< orphan*/  PVR_LIST_TR_POLY ; 
 int /*<<< orphan*/  dmadone ; 
 int /*<<< orphan*/  pvr_mem_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr_set_vertbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr_shutdown () ; 
 int /*<<< orphan*/  sem_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tex_space ; 
 int /*<<< orphan*/  vid_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void VIDDCDeInit(void)   {
    pvr_set_vertbuf(PVR_LIST_OP_POLY, NULL, 0);
    pvr_set_vertbuf(PVR_LIST_TR_POLY, NULL, 0);
    pvr_set_vertbuf(PVR_LIST_PT_POLY, NULL, 0);

    pvr_mem_free(tex_space);
    sem_destroy(&dmadone);

    pvr_shutdown();
    vid_set_mode(DM_640x480, PM_RGB565);
}