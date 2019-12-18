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
typedef  size_t const uint8_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/ * typefilter_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,size_t const) ; 

__attribute__((used)) static void typefilter_allow_class(typefilter_t tf, uint8_t class)
{
	assert(tf != NULL);
	const uint32_t BYTES_PER_CLASS = 256 / 8; // 256 subclasses, 1 bit each
	memset(&tf[class * BYTES_PER_CLASS], 0xFF, BYTES_PER_CLASS);
}