#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__** nextMap; } ;
typedef  TYPE_1__ TrieNode ;

/* Variables and functions */
 size_t Char2Index (char) ; 
 TYPE_1__* getNextChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  printf (char*,TYPE_1__*,char,TYPE_1__*) ; 

void setNextChar(TrieNode* t, char c, TrieNode* new)
{
    TrieNode* ptr = getNextChar(t, c);
    if(ptr != NULL)
        printf("warnning: already set next char %p %c %p\n", t, c, new);
    t->nextMap[Char2Index(c)] = new;
}