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
typedef  int /*<<< orphan*/  __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  inb (int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void Tdelay(__u16 scale)
{
	__u8 bTmp;
	int i, j;

	for (j = 0; j < scale; j++) {
		for (i = 0; i < 0x50; i++) {
			bTmp = inb(0xeb);
			outb(bTmp, 0xeb);
		}
	}
}