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
typedef  int /*<<< orphan*/  _TCHAR ;

/* Variables and functions */
 int N ; 
 int cout ; 
 int curMax ; 
 int /*<<< orphan*/  dfs (int /*<<< orphan*/ ) ; 
 int endl ; 
 int** map ; 
 int sumMax ; 

int _tmain(int argc, _TCHAR* argv[])
{
	curMax = map[0][0];
	dfs(0);
	cout << sumMax - map[N - 1][N - 1] << endl;
	return 0;
}