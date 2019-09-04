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
struct TYPE_3__ {char c; } ;
typedef  TYPE_1__ TrieNode ;

/* Variables and functions */

int compTrieNode(TrieNode* p, char c)
{
    if(p->c == c)
        return 0;
    else if(p->c > c)
        return 1;
    else
        return -1;
}