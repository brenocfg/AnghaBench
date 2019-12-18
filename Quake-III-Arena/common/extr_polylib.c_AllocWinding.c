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
typedef  int /*<<< orphan*/  winding_t ;
typedef  int /*<<< orphan*/  vec_t ;

/* Variables and functions */
 scalar_t__ c_active_windings ; 
 scalar_t__ c_peak_windings ; 
 int /*<<< orphan*/  c_winding_allocs ; 
 int c_winding_points ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int numthreads ; 

winding_t	*AllocWinding (int points)
{
	winding_t	*w;
	int			s;

	if (numthreads == 1)
	{
		c_winding_allocs++;
		c_winding_points += points;
		c_active_windings++;
		if (c_active_windings > c_peak_windings)
			c_peak_windings = c_active_windings;
	}
	s = sizeof(vec_t)*3*points + sizeof(int);
	w = malloc (s);
	memset (w, 0, s); 
	return w;
}