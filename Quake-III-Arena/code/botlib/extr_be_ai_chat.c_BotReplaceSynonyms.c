#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned long context; TYPE_1__* firstsynonym; struct TYPE_6__* next; } ;
typedef  TYPE_2__ bot_synonymlist_t ;
struct TYPE_7__ {int /*<<< orphan*/  string; struct TYPE_7__* next; } ;
typedef  TYPE_3__ bot_synonym_t ;
struct TYPE_5__ {int /*<<< orphan*/  string; TYPE_3__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  StringReplaceWords (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* synonyms ; 

void BotReplaceSynonyms(char *string, unsigned long int context)
{
	bot_synonymlist_t *syn;
	bot_synonym_t *synonym;

	for (syn = synonyms; syn; syn = syn->next)
	{
		if (!(syn->context & context)) continue;
		for (synonym = syn->firstsynonym->next; synonym; synonym = synonym->next)
		{
			StringReplaceWords(string, synonym->string, syn->firstsynonym->string);
		} //end for
	} //end for
}