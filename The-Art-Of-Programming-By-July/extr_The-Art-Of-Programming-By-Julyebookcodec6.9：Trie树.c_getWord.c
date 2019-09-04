#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int counter; } ;
typedef  TYPE_1__ TrieNode ;

/* Variables and functions */
 TYPE_1__* getNextChar (TYPE_1__*,char) ; 
 int strlen (char*) ; 

int getWord(TrieNode* t, char* word)
{
    int len = strlen(word);
    int tail = len - 1;
    for(int i = 0; i < len; i++)
    {
        char c = word[i];
        TrieNode* ptr = getNextChar(t, c);
        if(ptr != NULL)
        {
            t = ptr;
            if(i == tail)
                return t->counter;
        }else
            return 0;
    }
    return 0;
}