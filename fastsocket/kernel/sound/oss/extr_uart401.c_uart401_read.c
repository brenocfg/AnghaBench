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
typedef  int /*<<< orphan*/  uart401_devc ;

/* Variables and functions */
 int /*<<< orphan*/  DATAPORT ; 
 int inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uart401_read(uart401_devc * devc)
{
	return inb(DATAPORT);
}