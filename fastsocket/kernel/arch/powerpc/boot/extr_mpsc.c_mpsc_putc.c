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
 scalar_t__ MPSC_CHR_1 ; 
 scalar_t__ MPSC_CHR_2 ; 
 int MPSC_CHR_2_TCS ; 
 unsigned char chr1 ; 
 int chr2 ; 
 int in_le32 (int /*<<< orphan*/ *) ; 
 scalar_t__ mpsc_base ; 
 int /*<<< orphan*/  out_le32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mpsc_putc(unsigned char c)
{
	while (in_le32((u32 *)(mpsc_base + MPSC_CHR_2)) & MPSC_CHR_2_TCS);

	out_le32((u32 *)(mpsc_base + MPSC_CHR_1), chr1 | c);
	out_le32((u32 *)(mpsc_base + MPSC_CHR_2), chr2 | MPSC_CHR_2_TCS);
}