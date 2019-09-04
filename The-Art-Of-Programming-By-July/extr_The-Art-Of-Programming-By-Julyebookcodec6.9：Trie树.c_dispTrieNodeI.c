#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int c; int counter; struct TYPE_3__** nextMap; } ;
typedef  TYPE_1__ TrieNode ;

/* Variables and functions */
 int CHARSETSIZE ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  putchar (char) ; 

void dispTrieNodeI(TrieNode* t, int level)
{
    if(t == NULL)
        return;
    for(int i = 0; i < level; i++)
        putchar('\t');
    printf("%c %d\n", t->c, t->counter);
    int nextLevel = level + 1;
    for(int i = 0; i < CHARSETSIZE; i++)
    {
        dispTrieNodeI(t->nextMap[i], nextLevel);
    }
}