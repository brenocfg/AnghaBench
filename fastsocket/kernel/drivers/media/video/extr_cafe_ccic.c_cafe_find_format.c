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
typedef  scalar_t__ u32 ;
struct cafe_format_struct {scalar_t__ pixelformat; } ;

/* Variables and functions */
 unsigned int N_CAFE_FMTS ; 
 struct cafe_format_struct* cafe_formats ; 

__attribute__((used)) static struct cafe_format_struct *cafe_find_format(u32 pixelformat)
{
	unsigned i;

	for (i = 0; i < N_CAFE_FMTS; i++)
		if (cafe_formats[i].pixelformat == pixelformat)
			return cafe_formats + i;
	/* Not found? Then return the first format. */
	return cafe_formats;
}