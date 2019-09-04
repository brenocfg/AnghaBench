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
 int** dp ; 
 int min (int,int) ; 
 int strlen (char*) ; 

int editDistance(char *pSource, char *pTarget)
{
	int srcLength = strlen(pSource);
	int targetLength = strlen(pTarget);
	int i, j;
	//边界dp[i][0] = i，dp[0][j] = j  
	for (i = 1; i <= srcLength; ++i)
	{
		dp[i][0] = i;
	}
	for (j = 1; j <= targetLength; ++j)
	{
		dp[0][j] = j;
	}
	for (i = 1; i <= srcLength; ++i)
	{
		for (j = 1; j <= targetLength; ++j)
		{
			if (pSource[i - 1] == pTarget[j - 1])
			{
				dp[i][j] = dp[i - 1][j - 1];
			}
			else
			{
				dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}
	return dp[srcLength][targetLength];
}