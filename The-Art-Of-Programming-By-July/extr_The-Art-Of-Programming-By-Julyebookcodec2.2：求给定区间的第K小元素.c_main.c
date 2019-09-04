#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int data; } ;

/* Variables and functions */
 TYPE_1__* p ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  scanf (char*,int*,...) ; 
 int /*<<< orphan*/  sort (TYPE_1__*,TYPE_1__*) ; 

int main()     
{     
	int n=7;     
	int i,a,b,c;//c：flag;     

	for(i=1;i<=n;i++)      
	{     
		scanf("%d",&p[i].data);        
	}  

	scanf("%d%d%d", &a, &b, &c);   //b，a为原数组的下标索引  
	sort(p+a, p+b+1);     //直接对给定区间进行排序，|b-a+1|*log（b-a+1）  

	printf("The number is %d/n", p[a-1+c].data);      
	return 0;     
}