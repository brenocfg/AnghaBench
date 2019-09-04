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
 int N ; 
 scalar_t__ curMax ; 
 int** map ; 
 int p1x ; 
 int p1y ; 
 int p2x ; 
 int p2y ; 
 scalar_t__ sumMax ; 

void dfs( int index)
{
	if ( index == 2 * N - 2)
	{
		if ( curMax > sumMax)
			sumMax = curMax;
		return;
	}

	if ( !(p1x == 0 && p1y == 0) && !(p2x == N - 1 && p2y == N - 1))
	{
		if ( p1x >= p2x && p1y >= p2y )
			return;
	}

	//right right
	if ( p1x + 1 < N && p2x + 1 < N )
	{
		p1x++;
		p2x++;
		int sum = map[p1x][p1y] + map[p2x][p2y];
		curMax += sum;
		dfs(index + 1);
		curMax -= sum;
		p1x--;
		p2x--;
	}

	//down down
	if ( p1y + 1 < N && p2y + 1 < N )
	{
		p1y++;
		p2y++;
		int sum = map[p1x][p1y] + map[p2x][p2y];
		curMax += sum;
		dfs(index + 1);
		curMax -= sum;
		p1y--;
		p2y--;
	}

	//rd
	if ( p1x + 1 < N && p2y + 1 < N )
	{
		p1x++;
		p2y++;
		int sum = map[p1x][p1y] + map[p2x][p2y];
		curMax += sum;
		dfs(index + 1);
		curMax -= sum;
		p1x--;
		p2y--;
	}

	//dr
	if ( p1y + 1 < N && p2x + 1 < N )
	{
		p1y++;
		p2x++;
		int sum = map[p1x][p1y] + map[p2x][p2y];
		curMax += sum;
		dfs(index + 1);
		curMax -= sum;
		p1y--;
		p2x--;
	}
}