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
typedef  int /*<<< orphan*/ * PDEVICE_RD_INFO ;
typedef  int /*<<< orphan*/  DEVICE_RD_INFO ;

/* Variables and functions */
 scalar_t__ GFP_ATOMIC ; 
 scalar_t__ kmalloc (int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline PDEVICE_RD_INFO alloc_rd_info(void) {
    PDEVICE_RD_INFO  ptr;
    if ((ptr = (PDEVICE_RD_INFO)kmalloc((int)sizeof(DEVICE_RD_INFO), (int)GFP_ATOMIC)) == NULL)
        return NULL;
    else {
        memset(ptr,0,sizeof(DEVICE_RD_INFO));
        return ptr;
    }
}