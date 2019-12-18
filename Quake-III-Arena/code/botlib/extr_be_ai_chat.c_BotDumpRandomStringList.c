#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* string; struct TYPE_4__* next; } ;
typedef  TYPE_1__ bot_randomstring_t ;
struct TYPE_5__ {char* string; TYPE_1__* firstrandomstring; struct TYPE_5__* next; } ;
typedef  TYPE_2__ bot_randomlist_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * Log_FilePointer () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void BotDumpRandomStringList(bot_randomlist_t *randomlist)
{
	FILE *fp;
	bot_randomlist_t *random;
	bot_randomstring_t *rs;

	fp = Log_FilePointer();
	if (!fp) return;
	for (random = randomlist; random; random = random->next)
	{
		fprintf(fp, "%s = {", random->string);
		for (rs = random->firstrandomstring; rs; rs = rs->next)
		{
			fprintf(fp, "\"%s\"", rs->string);
			if (rs->next) fprintf(fp, ", ");
			else fprintf(fp, "}\n");
		} //end for
	} //end for
}