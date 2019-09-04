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
typedef  int /*<<< orphan*/  TrieNode ;

/* Variables and functions */
 int /*<<< orphan*/ * getNextChar (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  incTrieNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initTrieNode (int /*<<< orphan*/ *,char) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  setNextChar (int /*<<< orphan*/ *,char,int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 

void updateWord(TrieNode* t, char* word)
{

    TrieNode* ot = t;
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
                incTrieNode(t);
        }else
        {
            TrieNode* new = (TrieNode*)malloc(sizeof(TrieNode));
            initTrieNode(new, c);
            if(i == tail)
                incTrieNode(new);
            setNextChar(t, c, new);
            t = new;
        }
    }
}