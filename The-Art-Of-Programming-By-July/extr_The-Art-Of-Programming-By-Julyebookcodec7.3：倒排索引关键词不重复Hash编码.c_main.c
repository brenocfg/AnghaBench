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
 int /*<<< orphan*/  bigIndex_hash (char*,char*) ; 
 int /*<<< orphan*/  prepareCryptTable () ; 
 int /*<<< orphan*/  system (char*) ; 

int main()  
{  
	prepareCryptTable();  //Hash表起初要初始化  

	//现在要把整个big_index文件插入hash表，以取得编码结果  
	bigIndex_hash("big_index.txt", "hashpath.txt");  
	system("pause");  

	return 0;  
}