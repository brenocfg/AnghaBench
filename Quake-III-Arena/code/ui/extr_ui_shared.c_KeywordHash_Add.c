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
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  keyword; } ;
typedef  TYPE_1__ keywordHash_t ;

/* Variables and functions */
 int KeywordHash_Key (int /*<<< orphan*/ ) ; 

void KeywordHash_Add(keywordHash_t *table[], keywordHash_t *key) {
	int hash;

	hash = KeywordHash_Key(key->keyword);
/*
	if (table[hash]) {
		int collision = qtrue;
	}
*/
	key->next = table[hash];
	table[hash] = key;
}