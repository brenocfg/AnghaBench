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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARAM_READ ; 
 scalar_t__ AR_GetDMAStatus () ; 
 int /*<<< orphan*/  AR_StartDMA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DCInvalidateRange (char*,int) ; 

void ARAMFetch(char *dst, char *src, int len)
{
    DCInvalidateRange(dst, len);
    AR_StartDMA(ARAM_READ, (u32) dst, (u32) src, len);
    while (AR_GetDMAStatus());
}