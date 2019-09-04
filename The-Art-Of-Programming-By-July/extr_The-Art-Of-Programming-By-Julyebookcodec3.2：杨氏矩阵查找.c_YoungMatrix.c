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
 int COL ; 
 int ROW ; 

bool YoungMatrix(int array[][COL], int searchkey){
	int i = 0, j = COL - 1;
	int var = array[i][j];
	while (true){
		if (var == searchkey)
			return true;
		else if (var < searchkey && i < ROW - 1)
			var = array[++i][j];
		else if (var > searchkey && j > 0)
			var = array[i][--j];
		else
			return false;
	}
}