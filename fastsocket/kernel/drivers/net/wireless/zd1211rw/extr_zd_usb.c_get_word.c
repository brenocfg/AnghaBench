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
typedef  size_t u16 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 size_t le16_to_cpu (int /*<<< orphan*/  const) ; 

__attribute__((used)) static u16 get_word(const void *data, u16 offset)
{
	const __le16 *p = data;
	return le16_to_cpu(p[offset]);
}